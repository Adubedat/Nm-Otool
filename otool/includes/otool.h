/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:33:14 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/01 16:04:09 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "libft.h"
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <ar.h>

typedef struct			s_data
{
	char				*file_name;
	uint8_t				be;
	void				*ptr;
	size_t				file_size;
	uint8_t				sect_size;
	void				*sect[256];
	int					argc;
	int					arch;
	int					from_fat;
	int					from_archive;
	int					write_arch;
}						t_data;

typedef struct			s_sym_list
{
	char				*name;
	char				symbol;
	uint64_t			value;
	struct s_sym_list	*next;
}						t_sym_list;

int						open_error(char *file);
int						fstat_error(char *file);
int						mmap_error(char *file);
int						munmap_error(char *file);
int						close_error(char *file);
void					file_format_error(char *file);
void					truncated_file(char *file);
void					error_no_file(void);
void					not_object_file(char *file_name);
void					handle_lc64(struct mach_header_64 *ptr, t_data data);
void					handle_lc32(struct mach_header *ptr, t_data data);
void					handle_fat(struct fat_header *ptr, t_data data);
void					handle_ar(struct ar_hdr *ptr, t_data data);
char					get_symbol(uint8_t type, uint8_t sect,
		uint64_t value, t_data data);
void					print_lst(t_sym_list *lst, t_data data);
void					print_section64(struct section_64 sect, t_data *data);
void					print_section32(struct section sect, t_data *data);
void					print_file_name_ar(char *archive_name,
		char *object_name);
void					hexdump(void *memory, int len, uint64_t addr,
		t_data *data);
void					write_arch(cpu_type_t cpu_type, uint32_t march);
void					lstadd_ascii_sorted(t_sym_list **list,
		t_sym_list *new);
void					analyse_header(t_data data);
void					init_data(t_data *data);

#endif
