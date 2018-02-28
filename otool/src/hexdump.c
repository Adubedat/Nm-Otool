/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:58:15 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/28 22:14:57 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "otool.h"

void	ft_hexdump_char_otool(unsigned char *str, int len)
{
	int i;

	i = 0;
	ft_putstr("  ");
	while (i < len)
	{
		if ((str[i] >= 0 && str[i] <= 32)
			|| (str[i] >= 127))
			ft_putchar('.');
		else
			ft_putchar(str[i]);
		i++;
	}
	ft_putchar('\n');
}

void	print_byte_otool(unsigned char byte)
{
	char	*b;

	b = "0123456789abcdef";
	ft_putchar(b[byte / 16]);
	ft_putchar(b[byte % 16]);
	ft_putchar(' ');
}

void	print_zero(uint64_t addr, t_data *data)
{
	int	i;

	if (data->arch == 32)
		i = 8 - ft_hexalen(addr);
	if (data->arch == 64)
		i = 16 - ft_hexalen(addr);
	while (i > 0)
	{
		ft_putchar('0');
		i--;
	}
}

void	hexdump(void *memory, int len, uint64_t addr, t_data *data)
{
	unsigned char	*byte;
	int				i;

	i = 0;
	if (!memory)
		return ;
	byte = (unsigned char*)memory;
	print_zero(addr, data);
	ft_putnbr_hexa(addr);
	ft_putchar('\t');
	while (i < len)
	{
		if (i % 16 == 0 && i != 0)
		{
			ft_putchar('\n');
			print_zero(addr + i, data);
			ft_putnbr_hexa(addr + i);
			ft_putchar('\t');
		}
		print_byte_otool(byte[i++]);
	}
	ft_putchar('\n');
}
