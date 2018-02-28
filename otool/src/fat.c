/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:43:52 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/28 22:28:49 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include <mach-o/arch.h>

void		analyse_fat_arch32(struct fat_arch *fa, t_data data)
{
	uint32_t	offset;
	uint32_t	size;

	offset = (data.be) ? swap_uint32(fa->offset) : fa->offset;
	size = (data.be) ? swap_uint32(fa->size) : fa->size;
	if (offset + size > data.file_size)
		return (truncated_file(data.file_name));
	data.file_size = size;
	data.ptr = data.ptr + offset;
	analyse_header(data);
}

void		analyse_fat_arch64(struct fat_arch_64 *fa, t_data data)
{
	uint64_t	offset;
	uint64_t	size;

	offset = (data.be) ? swap_uint64(fa->offset) : fa->offset;
	size = (data.be) ? swap_uint64(fa->size) : fa->size;
	if (offset + size > data.file_size)
		return (truncated_file(data.file_name));
	data.file_size = size;
	data.ptr = data.ptr + offset;
	analyse_header(data);
}

void		handle_fat32(struct fat_header *ptr, t_data data, int all_arch)
{
	uint32_t			i;
	uint32_t			narch;
	cpu_type_t			fat_cputype;
	struct fat_arch		*fa;

	i = 0;
	narch = (data.be) ? swap_uint32(ptr->nfat_arch) : ptr->nfat_arch;
	fa = (struct fat_arch*)(ptr + 1);
	if (sizeof(struct fat_arch) * narch + sizeof(struct fat_header)
			> data.file_size)
		return (truncated_file(data.file_name));
	while (i++ < narch)
	{
		fat_cputype = (data.be) ? swap_uint32(fa->cputype) : fa->cputype;
		if (all_arch)
		{
			data.write_arch = fat_cputype;
			analyse_fat_arch32(fa, data);
		}
		else if (fat_cputype == CPU_TYPE_X86_64)
			return (analyse_fat_arch32(fa, data));
		fa = fa + 1;
	}
	if (!all_arch)
		handle_fat32(ptr, data, 1);
}

void		handle_fat64(struct fat_header *ptr, t_data data, int all_arch)
{
	uint32_t			i;
	uint32_t			narch;
	cpu_type_t			fat_cputype;
	struct fat_arch_64	*fa;

	i = 0;
	narch = (data.be) ? swap_uint32(ptr->nfat_arch) : ptr->nfat_arch;
	fa = (struct fat_arch_64*)(ptr + 1);
	if (sizeof(struct fat_arch_64) * narch + sizeof(struct fat_header)
			> data.file_size)
		return (truncated_file(data.file_name));
	while (i++ < narch)
	{
		fat_cputype = (data.be) ? swap_uint32(fa->cputype) : fa->cputype;
		if (all_arch)
		{
			data.write_arch = fat_cputype;
			analyse_fat_arch64(fa, data);
		}
		else if (fat_cputype == CPU_TYPE_X86_64)
			return (analyse_fat_arch64(fa, data));
		fa = fa + 1;
	}
	if (!all_arch)
		handle_fat64(ptr, data, 1);
}

void		handle_fat(struct fat_header *ptr, t_data data)
{
	data.from_fat = 1;
	if (ptr->magic == FAT_MAGIC || ptr->magic == FAT_CIGAM)
	{
		data.arch = 32;
		data.be = (ptr->magic == FAT_MAGIC) ? 0 : 1;
		handle_fat32(ptr, data, 0);
	}
	else if (ptr->magic == FAT_MAGIC_64 || ptr->magic == FAT_CIGAM_64)
	{
		data.arch = 64;
		data.be = (ptr->magic == FAT_MAGIC_64) ? 0 : 1;
		handle_fat64(ptr, data, 0);
	}
	else
		truncated_file(data.file_name);
}
