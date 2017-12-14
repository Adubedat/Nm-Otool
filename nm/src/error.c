/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:10:18 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/14 17:48:45 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	open_error(char *file)
{
	ft_putstr_fd("Error : open failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
}

void	fstat_error(char *file)
{
	ft_putstr_fd("Error : fstat failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
}

void	mmap_error(char *file)
{
	ft_putstr_fd("Error : mmap failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
}

void	munmap_error(char *file)
{
	ft_putstr_fd("Error : munmap failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
}

void	close_error(char *file)
{
	ft_putstr_fd("Error : close failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
}
