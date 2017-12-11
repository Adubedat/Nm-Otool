# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/18 19:13:31 by tvermeil          #+#    #+#              #
#    Updated: 2017/12/08 13:51:38 by adubedat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

SUB_MAKEFILES = libft \
				nm/src \
				otool/src \

all:
	@make -C libft all
	@make -C nm/src all
	@#@make -C otool/src all

libft.a:
	@make -C libft all

ft_nm:
	@make -C nm/src all

ft_otool:
	@make -C otool/src all

clean:
	@-for i in $(SUB_MAKEFILES) ; do \
		make -C $$i clean; \
	done
	@rmdir obj 2> /dev/null || true

fclean:
	@for i in $(SUB_MAKEFILES) ; do \
		make -C $$i fclean; \
	done

re: fclean all

ac: all clean

norme:
	@for i in $(SUB_MAKEFILES) ; do \
		make -C $$i norme; \
	done
	@norminette includes/*.h

.PHONY: all clean fclean re
