/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:00:44 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/12 14:56:45 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <mach-o/nlist.h>

void	handle_nlist64(struct nlist_64 symtab, char *strtab, int be,
	   	t_sym_list **lst)
{
	uint32_t	strx;
	uint64_t	value;
	t_sym_list	*new;

	if (symtab.n_type & N_STAB_MASK)
		return ;
	strx = (be) ? swap_uint32(symtab.n_un.n_strx) : symtab.n_un.n_strx;
	value = (be) ? swap_uint64(symtab.n_value) : symtab.n_value;
	new = (t_sym_list*)malloc(sizeof(t_sym_list));
	new->name = strtab + strx;
	new->symbol = get_symbol(symtab.n_type, symtab.n_sect);
	new->value = value;
	lstadd_ascii_sorted(lst, new);
}

void	parse_symtab(struct symtab_command *sc, void *ptr, int be)
{
	uint32_t		i;
	uint32_t		nsyms;
	struct nlist_64	*sym_tab;
	char			*string_table;
	t_sym_list		*lst;

	i = 0;
	lst = NULL;
	nsyms = (be) ? swap_uint32(sc->nsyms) : sc->nsyms;
	sym_tab = (be) ?  ptr + swap_uint32(sc->symoff) : ptr + sc->symoff;
	string_table = (be) ? ptr + swap_uint32(sc->stroff) : ptr + sc->stroff;
	while (i < nsyms)
	{
		handle_nlist64(sym_tab[i], string_table, be, &lst);
		i++;
	}
	print_lst(lst);
}

void	handle_lc64(struct mach_header_64 *ptr, int be, size_t file_size)
{
	uint32_t			i;
	uint32_t			ncmds;
	uint32_t			cmd;
	uint32_t			cmdsize;
	struct load_command	*lc;

	i = 0;
	ncmds = (be) ? swap_uint32(ptr->ncmds) : ptr->ncmds;
	lc = (struct load_command*)(ptr + 1);
	while (i++ < ncmds)
	{
		cmd = (be) ? swap_uint32(lc->cmd) : lc->cmd;
		cmdsize = (be) ? swap_uint32(lc->cmdsize) : lc->cmdsize;
		if ((size_t)((void*)lc + cmdsize - (void*)ptr) > file_size)
		{
			file_format_error();
			return ;	
		}
		if (cmd == LC_SYMTAB) 
		{
			parse_symtab((void*)lc, (void*)ptr, be);
			return ;
		}
		lc = (void*)lc + cmdsize;
	}
}
