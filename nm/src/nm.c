/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:20:15 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/12 18:38:52 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <sys/stat.h>
#include <sys/mman.h>

void	analyse_header(t_data data)
{
	uint32_t	magic_number;

	magic_number = *(unsigned int*)data.ptr;
	if ((magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM)
			&& data.file_size > (uint32_t)sizeof(struct mach_header_64))
	{
		data.be = (magic_number == MH_MAGIC_64) ? 0 : 1;
		handle_lc64(data.ptr, data);
	}
	else
		file_format_error();
}

void	nm(char *file)
{
	t_data		data;
	int			fd;
	struct stat	buf;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (open_error(file));
	if (fstat(fd, &buf) < 0)
	{
		fstat_error(file);
		return ;
	}
	data.file_size = buf.st_size;
	if ((data.ptr = mmap(0, data.file_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
	{
		mmap_error(file);
		return ;
	}
	analyse_header(data);
	if (munmap(data.ptr, data.file_size) < 0)
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
