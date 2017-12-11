/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:33:14 by adubedat          #+#    #+#             */
/*   Updated: 2017/12/11 21:23:00 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# define N_STAB_MASK	7 << 5

# include "libft.h"
# include <mach-o/loader.h>

void	open_error(char *file);
void	fstat_error(char *file);
void	mmap_error(char *file);
void	munmap_error(char *file);
void	close_error(char *file);
void	file_format_error(void);
void	handle_64(struct mach_header_64 *ptr, int endianness,
	   	size_t file_size);

#endif
