/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:22:16 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 20:04:05 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool		type_d(t_args *node, t_format *confgr, va_list args[2], char type)
{
	intmax_t	a;

	a = 0;
	if (type == 'D' && confgr->s_byte < sizeof(long))
		confgr->s_byte = sizeof(long);
	if (confgr->s_byte == sizeof(char))
		a = (char)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(short))
		a = (short)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(int))
		a = (int)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(long))
		a = (long)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(long long))
		a = (long long)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(size_t))
		a = (size_t)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(intmax_t))
		a = (intmax_t)ret_n_pos_ints(args, confgr->n_pos);
	if (!(node->arg = ft_itoa(a)))
		return (0);
	if (!(adjustment(node, confgr, 'd')))
		return (0);
	node->size = ft_strlen(node->arg);
	return (1);
}
