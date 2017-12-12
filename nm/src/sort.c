/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:14:53 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/12 15:02:12 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	lstadd_ascii_sorted(t_sym_list **list, t_sym_list *new)
{
	t_sym_list	*temp;

	temp = *list;
	if (temp == NULL || ft_strcmp(temp->name, new->name) > 0)
	{
		new->next = *list;
		*list = new;
		return ;
	}
	while (temp->next != NULL && ft_strcmp(temp->next->name, new->name) < 0)
		temp = temp->next;
	new->next = temp->next;
	temp->next = new;
}