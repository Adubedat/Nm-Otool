/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:33:14 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/12 18:40:43 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "libft.h"
# include <mach-o/loader.h>

typedef struct			s_data
{
	int					be;
	void				*ptr;
	size_t				file_size;
}						t_data;

typedef struct			s_sym_list
{
	char				*name;
	char				symbol;
	uint64_t			value;
	struct s_sym_list	*next;
}						t_sym_list;

void					open_error(char *file);
void					fstat_error(char *file);
void					mmap_error(char *file);
void					munmap_error(char *file);
void					close_error(char *file);
void					file_format_error(void);
void					handle_lc64(struct mach_header_64 *ptr,
		t_data data);
char					get_symbol(uint8_t type, uint8_t sect, t_data data);
void					print_lst(t_sym_list *lst);
void					lstadd_ascii_sorted(t_sym_list **list,
		t_sym_list *new);

#endif
