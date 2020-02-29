# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 18:49:17 by rtulchiy          #+#    #+#              #
#    Updated: 2020/02/29 10:16:45 by rtulchiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

OBJSRC = ft_malloc.c ft_realloc.c ft_free.c ft_free_sup.c support_func.c show.c alloc.c print.c print_sup.c

OBJC = $(OBJSRC:%.c=src/%.c)
OBJO = $(OBJSRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
LIBDIR = libft

%.o: src/%.c
	clang $(CFLAGS) -fPIC -c $< -pthread -I includes -mmacosx-version-min=10.0

all: $(NAME)

$(NAME): $(OBJO)
	make -C $(LIBDIR)
	clang $(CFLAGS) -shared -o $(NAME) $(OBJO) -L./$(LIBDIR) -lft -I ../includes -mmacosx-version-min=10.0
	ln -s $(NAME) libft_malloc.so

clean:
	make clean -C $(LIBDIR)
	rm -f $(OBJO)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f $(NAME) libft_malloc.so

re: fclean all
