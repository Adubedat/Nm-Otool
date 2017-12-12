/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:56:54 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/12 15:03:44 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <mach-o/nlist.h>

char	get_symbol(uint8_t type, uint8_t sect)
{
	char c;

	if (sect)
		;
	if ((type & N_ABS) == N_ABS)
		c = 'A';
	else if ((type & N_INDR) == N_INDR)
		c = 'I';
	else if ((type & N_SECT) == N_SECT)
		c = 'T';
	else
		c = 'U';
	return (c);
}
