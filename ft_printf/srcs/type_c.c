/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:21:59 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 19:47:29 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		handler_flag(t_args *node, t_format *confgr, char flag)
{
	if (flag)
	{
		node->size = ft_strlen(node->arg) + 1;
		if (confgr->f_alignment)
		{
			(node->arg)[ft_strlen(node->arg)] = ' ';
			*(node->arg) = 0;
		}
	}
}

static _Bool	unicode(t_args *node, wchar_t c)
{
	if (!(node->arg = (char*)ft_memalloc(5 * sizeof(char))))
		return (0);
	ft_putwchar(c, node->arg);
	return (1);
}

_Bool			type_c(t_args *node, t_format *confgr, va_list args[2],\
																char type)
{
	unsigned char	tmp;
	char			flag;

	flag = 0;
	if ((type == 'c' && confgr->s_byte != sizeof(long)) || MB_CUR_MAX == 1)
	{
		tmp = (unsigned char)ret_n_pos_ints(args, confgr->n_pos);
		if (!(node->arg = (char*)ft_memalloc(2 * sizeof(char))))
			return (0);
		*(node->arg) = tmp;
	}
	else if (type == 'C' || (type == 'c' && confgr->s_byte == sizeof(long)))
		if (!(unicode(node, (wchar_t)ret_n_pos_ints(args, confgr->n_pos))))
			return (0);
	if (!(*(node->arg)) && (flag = 1))
		(confgr->w_width)--;
	if (!(adjustment(node, confgr, 'c')))
		return (0);
	node->size = ft_strlen(node->arg);
	handler_flag(node, confgr, flag);
	return (1);
}
