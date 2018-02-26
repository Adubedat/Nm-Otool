/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:43:52 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/26 14:27:54 by adubedat         ###   ########.fr       */
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
	data.file_size = size;
	data.ptr = data.ptr + offset;
	analyse_header(data);
}

void		write_arch(cpu_type_t cpu_type, char* file_name, uint32_t narch)
{
	if (narch > 1)
		ft_putchar('\n');
	ft_putstr(file_name);
	if (narch > 1)
	{
		if (cpu_type == CPU_TYPE_X86)
			ft_putstr(" (for architecture i386):\n");
		else if (cpu_type == CPU_TYPE_POWERPC)
			ft_putstr(" (for architecture ppc):\n");
		else if (cpu_type == CPU_TYPE_X86_64)
			ft_putstr(" (for architecture x86_64):\n");
	}
	else
		ft_putstr(":\n");
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
			write_arch(fat_cputype, data.file_name, narch);
			analyse_fat_arch(fa, data);
		}
		else if (fat_cputype == CPU_TYPE_X86_64)
			return (analyse_fat_arch(fa, data));
		fa = fa + 1;
	}
	if (!all_arch)
		handle_fat32(ptr, data, 1);
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
	else
		truncated_file(data.file_name);
}
