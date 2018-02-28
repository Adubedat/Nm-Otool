/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:20:15 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/28 22:26:06 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
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
		handle_fat(data.ptr, data);
	else if (ft_strncmp((char*)data.ptr, ARMAG, SARMAG) == 0
			&& data.file_size > SARMAG + (uint32_t)sizeof(struct ar_hdr))
		handle_ar(data.ptr + SARMAG, data);
	else
		not_object_file(data.file_name);
}

void	otool(t_data data)
{
	int			fd;
	struct stat	buf;

	if ((fd = open(data.file_name, O_RDONLY)) < 0)
		return (open_error(data.file_name));
	if (fstat(fd, &buf) < 0)
	{
		fstat_error(data.file_name);
		return ;
	}
	data.file_size = buf.st_size;
	if ((data.ptr = mmap(0, data.file_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
	{
		mmap_error(data.file_name);
		return ;
	}
	analyse_header(data);
	if (munmap(data.ptr, data.file_size) < 0)
		munmap_error(data.file_name);
	if (close(fd) < 0)
		close_error(data.file_name);
}

void	init_data(t_data *data)
{
	data->file_name = NULL;
	data->be = 0;
	data->ptr = NULL;
	data->file_size = 0;
	data->sect_size = 0;
	data->argc = 0;
	data->arch = 0;
	data->from_fat = 0;
	data->from_archive = 0;
	data->write_arch = 0;
}

int		main(int argc, char **argv)
{
	int	i;
	t_data	data;

	init_data(&data);
	data.argc = argc;
	if (argc == 1)
	{
		error_no_file();
		return (EXIT_FAILURE);
	}
	else
	{
		i = 1;
		while (argv[i])
		{
			data.file_name = argv[i];
			otool(data);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
