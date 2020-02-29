# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 18:49:17 by rtulchiy          #+#    #+#              #
#    Updated: 2020/02/29 12:53:20 by rtulchiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

OBJSRC = ft_malloc.c ft_realloc.c ft_free.c ft_free_sup.c support_func.c show.c alloc.c print.c print_sup.c \
		 ft_bzero.c ft_memcpy.c ft_memset.c ft_strlen.c log.c

OBJC = $(OBJSRC:%.c=src/%.c)
OBJO = $(OBJSRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra -g

%.o: src/%.c
	cc $(CFLAGS) -fPIC -c $< -pthread -I includes -D_GNU_SOURCE

all: $(NAME)

$(NAME): $(OBJO)
	cc $(CFLAGS) -shared -fPIC -o $(NAME) $(OBJO) -I ../includes
	ln -s $(NAME) libft_malloc.so

clean:
	rm -f $(OBJO)

fclean: clean
	rm -f $(NAME) libft_malloc.so

re: fclean all
