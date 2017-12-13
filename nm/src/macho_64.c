/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:00:44 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/13 19:02:28 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <mach-o/nlist.h>

int		handle_nlist64(struct nlist_64 symtab, char *strtab, t_data data,
	   	t_sym_list **lst)
{
	uint32_t	strx;
	uint64_t	value;
	t_sym_list	*new;

	if (symtab.n_type & N_STAB)
		return (0);
	strx = (data.be) ? swap_uint32(symtab.n_un.n_strx) : symtab.n_un.n_strx;
	value = (data.be) ? swap_uint64(symtab.n_value) : symtab.n_value;
	new = (t_sym_list*)malloc(sizeof(t_sym_list));
	if ((size_t)((void*)strtab + strx - data.ptr) > data.file_size)
		return (-1);
	new->name = strtab + strx;
	new->symbol = get_symbol(symtab.n_type, symtab.n_sect, value, data);
	new->value = value;
	lstadd_ascii_sorted(lst, new);
	return (0);
}

void	parse_symtab(struct symtab_command *sc, t_data data)
{
	uint32_t		i;
	uint32_t		nsyms;
	struct nlist_64	*sym_tab;
	char			*string_table;
	t_sym_list		*lst;

	i = 0;
	lst = NULL;
	nsyms = (data.be) ? swap_uint32(sc->nsyms) : sc->nsyms;
	sym_tab = (data.be) ? data.ptr + swap_uint32(sc->symoff)
		: data.ptr + sc->symoff;
	string_table = (data.be) ? data.ptr + swap_uint32(sc->stroff)
		: data.ptr + sc->stroff;
	while (i < nsyms)
	{
		if ((size_t)((void*)&sym_tab[i + 1] - data.ptr) > data.file_size)
			return (file_format_error());
		if (handle_nlist64(sym_tab[i], string_table, data, &lst) == -1)
			return (file_format_error());
		i++;
	}
	print_lst(lst);
}

int		parse_segment64(struct segment_command_64 *segc, t_data *data)
{
	uint32_t			nsects;
	uint64_t			fileoff;
	uint64_t			filesize;
	struct section_64	*sect64;
	uint32_t			i;

	nsects = (data->be) ? swap_uint64(segc->nsects) : segc->nsects;
	fileoff = (data->be) ? swap_uint64(segc->fileoff) : segc->fileoff;
	filesize = (data->be) ? swap_uint64(segc->filesize) : segc->filesize;
	sect64 = (void*)segc + sizeof(*segc);
	i = 0;
	if (fileoff + filesize > data->file_size)
		return (-1);
	if (nsects == 0)
		return (0);
	while (i < nsects)
	{
		data->sect[i + data->sect_size] = &sect64[i];
		i++;
	}
	data->sect_size += nsects;
	return (0);
}

void	handle_lc64(struct mach_header_64 *ptr, t_data data)
{
	uint32_t			i;
	uint32_t			ncmds;
	uint32_t			cmd;
	uint32_t			cmdsize;
	struct load_command	*lc;

	i = 0;
	ncmds = (data.be) ? swap_uint32(ptr->ncmds) : ptr->ncmds;
	lc = (struct load_command*)(ptr + 1);
	while (i++ < ncmds)
	{
		cmd = (data.be) ? swap_uint32(lc->cmd) : lc->cmd;
		cmdsize = (data.be) ? swap_uint32(lc->cmdsize) : lc->cmdsize;
		if ((size_t)((void*)lc + cmdsize - (void*)ptr) > data.file_size)
			return (file_format_error());
		if (cmd == LC_SEGMENT_64 && (parse_segment64((void*)lc, &data) == -1))
			return (file_format_error());
		if (cmd == LC_SYMTAB) 
			return (parse_symtab((void*)lc, data));
		lc = (void*)lc + cmdsize;
	}
}
