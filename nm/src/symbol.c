/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:56:54 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/12 18:44:06 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <mach-o/nlist.h>

char	parse_segment(uint8_t sect, t_data data)
{

	return ('T');
}

char	get_symbol(uint8_t type, uint8_t sect, t_data data)
{
	char c;

	if (sect)
		;
	if ((type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((type & N_TYPE) == N_INDR)
		c = 'I';
	else if ((type & N_TYPE) == N_SECT)
		c = parse_segment(sect, data);
	else if ((type & N_TYPE) == N_PBUD)
		c = 'P';
	else
		c = 'U';
	return (c);
}
