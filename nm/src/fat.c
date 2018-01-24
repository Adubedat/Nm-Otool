/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:43:52 by adubedat          #+#    #+#             */
/*   Updated: 2018/01/23 17:57:28 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <mach-o/arch.h>

void		analyse_fat_arch(struct fat_arch *fa, t_data data)
{
	uint32_t	offset;
	uint32_t	size;

	offset = (data.be) ? swap_uint32(fa->offset) : fa->offset;
	size = (data.be) ? swap_uint32(fa->size) : fa->size;
	if (offset + size > data.file_size)
		return (truncated_file(data.file_name));
	data.file_size = fa->size;
	data.ptr = data.ptr + offset;
	analyse_header(data);
}

void		analyse_all_fat_arch(struct fat_header *ptr, t_data data)
{
	(void)ptr;
	(void)data;
	ft_printf("cputype not founded\n");
}

void		handle_fat32(struct fat_header *ptr, t_data data)
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
		if (fat_cputype == CPU_TYPE_X86_64)
			return (analyse_fat_arch(fa, data));
		fa = fa + 1;
	}
	analyse_all_fat_arch(ptr, data);
}

void		handle_fat(struct fat_header *ptr, t_data data)
{
	if (ptr->magic == FAT_MAGIC || ptr->magic == FAT_CIGAM)
	{
		data.be = (ptr->magic == FAT_MAGIC) ? 0 : 1;
		handle_fat32(ptr, data);
	}
	else
		truncated_file(data.file_name);
}
