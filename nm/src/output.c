/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:09:00 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/13 13:30:34 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_lst(t_sym_list *lst)
{
	t_sym_list	*temp;

	while (lst != NULL)
	{
		if (lst->symbol != 'U')
			ft_printf("%016llx ", lst->value);
		else
			ft_putstr("                 ");
		ft_putchar(lst->symbol);
		ft_putchar(' ');
		ft_putstr(lst->name);
		ft_putchar('\n');
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}
