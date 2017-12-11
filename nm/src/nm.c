/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:20:15 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/11 19:29:59 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <sys/stat.h>
#include <sys/mman.h>

void	analyse_header(void *ptr, unsigned long file_size)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int*)ptr;
	if (magic_number == MH_MAGIC_64
			&& file_size > sizeof(struct mach_header_64))
		handle_64(ptr, 0, file_size);
	else if (magic_number == MH_CIGAM_64)
		handle_64(ptr, 1, file_size);
	else
		file_format_error();
}

void	nm(char *file)
{
	int			fd;
	struct stat	buf;
	void		*ptr;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		open_error(file);
		return ;
	}
	if (fstat(fd, &buf) < 0)
	{
		fstat_error(file);
		return ;
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
	{
		mmap_error(file);
		return ;
	}
	analyse_header(ptr, buf.st_size);
	if (munmap(ptr, buf.st_size) < 0)
		munmap_error(file);
	if (close(fd) < 0)
		close_error(file);
}

int		main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		nm("a.out");
	else
	{
		i = 1;
		while (argv[i])
		{
			nm(argv[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
