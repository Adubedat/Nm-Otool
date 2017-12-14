/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:55:49 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/14 17:49:16 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	file_format_error(char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" was not recognized as a valid object file\n", 2);
}

void	truncated_file(char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" is truncated or malformated\n", 2);
}
