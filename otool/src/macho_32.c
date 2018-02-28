/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:00:44 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/28 22:08:28 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include <mach-o/nlist.h>

int		parse_segment32(struct segment_command *segc, t_data *data)
{
	uint32_t			nsects;
	uint32_t			fileoff;
	uint32_t			filesize;
	struct section		*sect32;
	uint32_t			i;

	nsects = (data->be) ? swap_uint32(segc->nsects) : segc->nsects;
	fileoff = (data->be) ? swap_uint32(segc->fileoff) : segc->fileoff;
	filesize = (data->be) ? swap_uint32(segc->filesize) : segc->filesize;
	sect32 = (void*)segc + sizeof(*segc);
	i = 0;
	if (fileoff + filesize > data->file_size)
		return (-1);
	if (nsects == 0)
		return (0);
	while (i < nsects)
	{
		if (ft_strcmp(sect32[i].sectname, SECT_TEXT) == 0)
			print_section32(sect32[i], data);
		i++;
	}
	data->sect_size += nsects;
	return (0);
}

void	handle_lc32(struct mach_header *ptr, t_data data)
{
	uint32_t			i;
	uint32_t			ncmds;
	uint32_t			cmd;
	uint32_t			cmdsize;
	struct load_command	*lc;

	ft_putstr(data.file_name);
	i = 0;
	data.arch = 32;
	ncmds = (data.be) ? swap_uint32(ptr->ncmds) : ptr->ncmds;
	lc = (struct load_command*)(ptr + 1);
	while (i++ < ncmds)
	{
		cmd = (data.be) ? swap_uint32(lc->cmd) : lc->cmd;
		cmdsize = (data.be) ? swap_uint32(lc->cmdsize) : lc->cmdsize;
		if ((size_t)((void*)lc + cmdsize - (void*)ptr) > data.file_size)
			return (truncated_file(data.file_name));
		if (cmd == LC_SEGMENT && (parse_segment32((void*)lc, &data) == -1))
			return (truncated_file(data.file_name));
		lc = (void*)lc + cmdsize;
	}
}
