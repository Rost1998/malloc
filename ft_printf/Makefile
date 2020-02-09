# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/21 20:17:39 by rtulchiy          #+#    #+#              #
#    Updated: 2018/02/16 22:56:34 by rtulchiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ = ft_printf.o srcs/a_adjustment.o srcs/a_width.o\
	  srcs/handle_main.o srcs/parser.o\
	  srcs/type_c.o srcs/type_g.o\
	  srcs/type_s.o srcs/a_precision.o\
	  srcs/addition.o srcs/handle_type.o\
	  srcs/percent.o srcs/type_d.o srcs/type_n.o\
	  srcs/type_u.o srcs/a_prefix.o\
	  srcs/dollar_handle.o srcs/handles.o\
	  srcs/priority.o srcs/type_e.o\
	  srcs/type_o.o srcs/type_x.o srcs/a_sign.o\
	  srcs/get_exp.o srcs/infnan_handle.o\
	  srcs/type_b.o srcs/type_f.o srcs/type_p.o srcs/whatisit.o\
	  srcs/rounding.o libft/ft_atoi.o libft/ft_itoa_base.o\
	  libft/ft_memmove.o libft/ft_putstr.o\
	  libft/ft_revbits.o libft/ft_isdigit.o libft/ft_itoafloat.o\
	  libft/ft_memset.o libft/ft_putwchar.o\
	  libft/ft_strlen.o libft/ft_iswhitespaces.o libft/ft_memalloc.o\
	  libft/ft_pow.o libft/ft_realloc.o\
	  libft/ft_uitoa.o libft/ft_itoa.o libft/ft_memcpy.o\
	  libft/ft_putnbr.o libft/ft_revarr.o

OBJ2 = ft_printf.o a_adjustment.o a_width.o\
	  handle_main.o parser.o type_c.o type_g.o\
	  type_s.o a_precision.o addition.o handle_type.o\
	  percent.o type_d.o type_u.o a_prefix.o\
	  dollar_handle.o handles.o priority.o type_e.o\
	  type_o.o type_x.o a_sign.o get_exp.o infnan_handle.o\
	  type_b.o type_f.o type_p.o type_n.o whatisit.o\
	  rounding.o ft_atoi.o ft_itoa_base.o\
	  ft_memmove.o ft_putstr.o ft_revbits.o ft_isdigit.o ft_itoafloat.o\
	  ft_memset.o ft_putwchar.o ft_strlen.o ft_iswhitespaces.o ft_memalloc.o\
	  ft_pow.o ft_realloc.o ft_uitoa.o ft_itoa.o ft_memcpy.o\
	  ft_putnbr.o ft_revarr.o

NAME = libftprintf.a
INCLUDES = includes/libftprintf.h
CFLAGS = -Wall -Werror -Wextra

%.o: %.c $(INCLUDES)
	gcc $(CFLAGS) -fPIC -c $< -I includes

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ2)
	ranlib $(NAME)
clean:
	rm -f $(OBJ2)
fclean: clean
	rm -f $(NAME)
re: fclean all
