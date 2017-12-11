/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:10:18 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/08 14:19:58 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	open_error(char *file)
{
	ft_putstr("Error : open failed for ");
	ft_putstr(file);
	ft_putchar('\n');
}

void	fstat_error(char *file)
{
	ft_putstr("Error : fstat failed for ");
	ft_putstr(file);
	ft_putchar('\n');
}

void	mmap_error(char *file)
{
	ft_putstr("Error : mmap failed for ");
	ft_putstr(file);
	ft_putchar('\n');
}

void	munmap_error(char *file)
{
	ft_putstr("Error : munmap failed for ");
	ft_putstr(file);
	ft_putchar('\n');
}

void	close_error(char *file)
{
	ft_putstr("Error : close failed for ");
	ft_putstr(file);
	ft_putchar('\n');
}
