/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:09:00 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/26 14:01:10 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	print_line32(t_sym_list *lst)
{
	if (lst->symbol != 'U')
		ft_printf("%08llx ", lst->value);
	else
		ft_putstr("         ");
	ft_putchar(lst->symbol);
	ft_putchar(' ');
	ft_putstr(lst->name);
	ft_putchar('\n');
}

void	print_line64(t_sym_list *lst)
{
	if (lst->symbol != 'U')
		ft_printf("%016llx ", lst->value);
	else
		ft_putstr("                 ");
	ft_putchar(lst->symbol);
	ft_putchar(' ');
	ft_putstr(lst->name);
	ft_putchar('\n');
}

void	print_lst(t_sym_list *lst, t_data data)
{
	t_sym_list	*temp;

	if (data.argc > 2 && !data.from_fat && !data.from_archive && lst != NULL)
		ft_printf("\n%s:\n", data.file_name);
	while (lst != NULL)
	{
		if (data.arch == 64)
			print_line64(lst);
		else if (data.arch == 32)
			print_line32(lst);
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}
