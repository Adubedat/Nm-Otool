/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:16:32 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/28 21:33:43 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	not_object_file(char *file_name)
{
	ft_putstr(file_name);
	ft_putstr(": is not an object file\n");
}

void	error_no_file(void)
{
	ft_putstr_fd("Error: at least one file must be specified\n", 2);
}
