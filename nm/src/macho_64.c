/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:00:44 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/11 22:22:28 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <mach-o/nlist.h>

void	parse_symtab(struct symtab_command *sc, void *ptr, int endianness)
{
	uint32_t		i;
	struct nlist_64	*sym_tab;
	char			*string_table;

	i = 0;
	sym_tab = ptr + sc->symoff;
	string_table = ptr + sc->stroff;
	ft_putstr("symtab started\n");
	if (endianness)
		;
	while (i < sc->nsyms)
	{
		if (!(sym_tab[i].n_type & N_STAB_MASK))
		{
			if (sym_tab[i].n_value != 0)
				ft_printf("%016llx ", sym_tab[i].n_value);
			else
				ft_putstr("                 ");
			ft_putstr(string_table + sym_tab[i].n_un.n_strx);
			ft_putchar('\n');
	//		ft_printf("%x\n", sym_tab[i].n_type);
	//		ft_printf("%x\n", sym_tab[i].n_sect);
	//		ft_printf("%x\n", sym_tab[i].n_desc);
	//		ft_printf("%x\n", sym_tab[i].n_value);
		}
		i++;
	}
}

void	handle_64(struct mach_header_64 *ptr, int endianness, size_t file_size)
{
	int					i;
	int					ncmds;
	struct load_command	*lc;

	i = 0;
	ncmds = ptr->ncmds;
	lc = (struct load_command*)(ptr + 1);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB 
			&& (size_t)((void*)lc + lc->cmdsize - 1 - (void*)ptr) <= file_size)
		{
			parse_symtab((void*)lc, (void*)ptr, endianness);
			return;
		}
		if ((size_t)((void*)lc + lc->cmdsize - (void*)ptr) > file_size)
		{
			file_format_error();
			return ;	
		}
		i++;
		lc = (void*)lc + lc->cmdsize;
	}
}
