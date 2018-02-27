/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:23:51 by adubedat          #+#    #+#             */
/*   Updated: 2018/02/27 17:32:31 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		analyse_object(struct ar_hdr *ptr, char *archive_name)
{
	t_data	data;
	size_t	file_name_size;

	file_name_size = ft_atoi((void*)ptr->ar_name + ft_strlen(AR_EFMT1));
	init_data(&data);
	data.file_name = (char*)(ptr + 1);
	data.file_size = ft_atoi(ptr->ar_size);
	data.ptr = (void*)ptr + sizeof(*ptr) + file_name_size;
	ft_printf("\n%s(%s):\n", archive_name, data.file_name);
	analyse_header(data);
}

void		handle_ar(struct ar_hdr *ptr, t_data data)
{
	size_t	size;

	size = ft_atoi(ptr->ar_size);
	if ((size_t)((void*)ptr + size + sizeof(*ptr) - data.ptr) > data.file_size)
		return (truncated_file(data.file_name));
	ptr = (void*)ptr + sizeof(*ptr) + size;
	while ((size_t)((void*)ptr - data.ptr) < data.file_size + 1)
	{
		size = ft_atoi(ptr->ar_size);
		if ((size_t)((void*)ptr + sizeof(*ptr) + size - data.ptr) > data.file_size)
			return (truncated_file(data.file_name));
		analyse_object(ptr, data.file_name);
		ptr = (void*)ptr + sizeof(*ptr) + size;
	}
}
