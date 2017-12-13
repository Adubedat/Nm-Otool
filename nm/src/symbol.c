/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:56:54 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/13 19:03:21 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <mach-o/nlist.h>

char	parse_section(uint8_t type, uint8_t n_sect, t_data data)
{
	char	c;
	char	*sectname;

	c = 'I';
	sectname = ((struct section_64 *)data.sect[n_sect - 1])->sectname;
	if (ft_strcmp(sectname, SECT_TEXT) == 0)
		c = (type & N_EXT) ? 'T' : 't';
	else if (ft_strcmp(sectname, SECT_DATA) == 0)
		c = (type & N_EXT) ? 'D' : 'd';
	else if (ft_strcmp(sectname, SECT_BSS) == 0)
		c = (type & N_EXT) ? 'B' : 'b';
	else
		c = (type & N_EXT) ? 'S' : 's';
	return (c);
}

char	get_symbol(uint8_t type, uint8_t sect, uint64_t value, t_data data)
{
	char c;

	if (sect)
		;
	if ((type & N_TYPE) == N_ABS)
		c = (type & N_EXT) ? 'A' : 'a';
	else if ((type & N_TYPE) == N_INDR)
		c = (type & N_EXT) ? 'I' : 'i';
	else if ((type & N_TYPE) == N_SECT)
		c = parse_section(type, sect, data);
	else
	{
		if ((type & N_EXT) && value != 0)
			c = 'C';
		else
			c = (type & N_EXT) ? 'U' : 'u';
	}
	return (c);
}
