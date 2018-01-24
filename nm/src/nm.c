/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:20:15 by adubedat          #+#    #+#             */
/*   Updated: 2018/01/23 10:58:36 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <sys/stat.h>
#include <sys/mman.h>

void	analyse_header(t_data data)
{
	uint32_t	magic_number;

	magic_number = *(unsigned int*)data.ptr;
	if ((magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
			&& data.file_size > (uint32_t)sizeof(struct mach_header_64))
	{
		data.be = (magic_number == MH_MAGIC_64) ? 0 : 1;
		handle_lc64(data.ptr, data);
	}
	else if ((magic_number == MH_MAGIC || magic_number == MH_CIGAM)
			&& data.file_size > (uint32_t)sizeof(struct mach_header))
	{
		data.be = (magic_number == MH_MAGIC) ? 0 : 1;
		handle_lc32(data.ptr, data);
	}
	else if ((magic_number == FAT_MAGIC || magic_number == FAT_CIGAM
			|| magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
			&& data.file_size > (uint32_t)sizeof(struct fat_header))
	{
		handle_fat(data.ptr, data);
	}
	else
		file_format_error(data.file_name);
}

void	nm(char *file)
{
	t_data		data;
	int			fd;
	struct stat	buf;

	data.file_name = file;
	data.sect_size = 0;
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
			if (argc > 2)
				ft_printf("\n%s:\n", argv[i]);
			nm(argv[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
