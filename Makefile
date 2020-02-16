# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 18:49:17 by rtulchiy          #+#    #+#              #
#    Updated: 2018/02/25 13:15:22 by rtulchiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

OBJSRC = ft_malloc.c

OBJC = $(OBJSRC:%.c=src/%.c)
OBJO = $(OBJSRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
LIBDIR = libft
FT_PRINTF = ft_printf

%.o: src/%.c
	gcc $(CFLAGS) -fPIC -c $< -pthread -I includes

all: $(NAME)
	ln -s $(NAME) libft_malloc.so

$(NAME): $(OBJO)
	make -C $(LIBDIR)
	make -C $(FT_PRINTF)
	gcc $(CFLAGS) -shared -o $(NAME) $(OBJO) -L./$(LIBDIR) -L./ft_printf -lftprintf -lft -pthread -I ../includes

clean:
	make clean -C $(LIBDIR)
	make clean -C $(FT_PRINTF)
	rm -f $(OBJO)

fclean: clean
	make fclean -C $(LIBDIR)
	make fclean -C $(FT_PRINTF)
	rm -f $(NAME) libft_malloc.so

re: fclean all
