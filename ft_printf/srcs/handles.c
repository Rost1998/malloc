/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:02:34 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/20 18:48:58 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	handle_flags(const char **modf, t_format *confgr)
{
	while (isflags(**modf))
	{
		if (**modf == '-')
			confgr->f_alignment = 1;
		else if (**modf == '+')
			confgr->f_plus = 1;
		else if (**modf == ' ')
			confgr->f_space = 1;
		else if (**modf == '#')
			confgr->f_diez = 1;
		else if (**modf == '0')
			confgr->f_fill = 1;
		else if (**modf == '\'')
			confgr->f_apostr = 1;
		(*modf)++;
	}
}

void	handle_width(const char **modf, t_format *confgr, va_list args[2])
{
	if (**modf == '*')
	{
		(*modf)++;
		if (isdollar(*modf))
			confgr->w_width = (int)ret_n_pos_ints(args, check_n_pos(modf));
		else
			confgr->w_width = va_arg(args[1], int);
		if (confgr->w_width < 0)
		{
			confgr->w_width *= -1;
			confgr->f_alignment = 1;
		}
	}
	else
		confgr->w_width = ft_atoi(modf);
}

void	handle_precision(const char **modf, t_format *confgr, va_list args[2])
{
	(*modf)++;
	if (**modf == '*')
	{
		(*modf)++;
		if (isdollar(*modf))
			confgr->p_prec = ret_n_pos_ints(args, check_n_pos(modf));
		else
			confgr->p_prec = va_arg(args[1], int);
	}
	else
		confgr->p_prec = ft_atoi(modf);
}

void	handle_modfsize(const char **modf, t_format *confgr)
{
	if ((*modf)[0] == 'l' && (*modf)[1] != 'l' && confgr->s_byte < sizeof(long))
		confgr->s_byte = sizeof(long);
	else if ((*modf)[0] == 'l' && (*modf)[1] == 'l' &&\
											confgr->s_byte < sizeof(long long))
		confgr->s_byte = sizeof(long long);
	else if ((*modf)[0] == 'h' && (*modf)[1] != 'h' &&\
											confgr->s_byte < sizeof(short))
		confgr->s_byte = sizeof(short);
	else if ((*modf)[0] == 'h' && (*modf)[1] == 'h' &&\
											confgr->s_byte < sizeof(char))
		confgr->s_byte = sizeof(char);
	else if ((*modf)[0] == 'j' && confgr->s_byte < sizeof(intmax_t))
		confgr->s_byte = sizeof(intmax_t);
	else if ((*modf)[0] == 'z' && confgr->s_byte < sizeof(size_t))
		confgr->s_byte = sizeof(size_t);
	(*modf)++;
	if (**modf == 'h' || **modf == 'l')
		(*modf)++;
}
