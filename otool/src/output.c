/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:09:00 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/28 22:29:42 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void		print_section32(struct section sect, t_data *data)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	addr;

	if (data->write_arch)
		write_arch(data->write_arch, 2);
	ft_putstr(":\n");
	ft_putstr("Contents of (__TEXT,__text) section\n");
	offset = (data->be) ? swap_uint32(sect.offset) : sect.offset;
	addr = (data->be) ? swap_uint32(sect.addr) : sect.addr;
	size = (data->be) ? swap_uint32(sect.size) : sect.size;
	if (offset + size > data->file_size)
		return (truncated_file(data->file_name));
	hexdump(data->ptr + offset, size, addr, data);
}

void		print_section64(struct section_64 sect, t_data *data)
{
	uint32_t	offset;
	uint64_t	size;
	uint64_t	addr;

	if (data->write_arch)
		write_arch(data->write_arch, 2);
	ft_putstr(":\n");
	ft_putstr("Contents of (__TEXT,__text) section\n");
	offset = (data->be) ? swap_uint32(sect.offset) : sect.offset;
	size = (data->be) ? swap_uint64(sect.size) : sect.size;
	addr = (data->be) ? swap_uint64(sect.addr) : sect.addr;
	if (offset + size > data->file_size)
		return (truncated_file(data->file_name));
	hexdump(data->ptr + offset, size, addr, data);
}

void		print_file_name_ar(char *archive_name, char *object_name)
{
	ft_putstr(archive_name);
	ft_putchar('\n');
	ft_putstr(object_name);
	ft_putchar(')');
}

void		write_arch(cpu_type_t cpu_type, uint32_t narch)
{
	if (narch > 1)
	{
		if (cpu_type == CPU_TYPE_X86)
			ft_putstr(" (architecture i386)");
		else if (cpu_type == CPU_TYPE_POWERPC)
			ft_putstr(" (architecture ppc)");
		else if (cpu_type == CPU_TYPE_X86_64)
			ft_putstr(" (architecture x86_64)");
	}
	else
		ft_putstr(":\n");
}
