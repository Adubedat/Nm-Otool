/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:10:18 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/01 16:06:01 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		open_error(char *file)
{
	ft_putstr_fd("Error : open failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int		fstat_error(char *file)
{
	ft_putstr_fd("Error : fstat failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int		mmap_error(char *file)
{
	ft_putstr_fd("Error : mmap failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int		munmap_error(char *file)
{
	ft_putstr_fd("Error : munmap failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int		close_error(char *file)
{
	ft_putstr_fd("Error : close failed for ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}
