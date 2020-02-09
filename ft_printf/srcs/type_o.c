/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:30:29 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 10:42:02 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool	type_o(t_args *node, t_format *confgr, va_list args[2], char type)
{
	uintmax_t	a;

	a = 0;
	if (type == 'O' && confgr->s_byte < sizeof(long))
		confgr->s_byte = sizeof(unsigned long);
	if (confgr->s_byte == sizeof(unsigned char))
		a = (unsigned char)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(unsigned short))
		a = (unsigned short)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(unsigned int))
		a = (unsigned int)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(unsigned long))
		a = (unsigned long)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(unsigned long long))
		a = (unsigned long long)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(size_t))
		a = (size_t)ret_n_pos_ints(args, confgr->n_pos);
	else if (confgr->s_byte == sizeof(uintmax_t))
		a = (uintmax_t)ret_n_pos_ints(args, confgr->n_pos);
	if (!(node->arg = ft_itoa_base(a, 8, 0)))
		return (0);
	if (!(adjustment(node, confgr, 'o')))
		return (0);
	node->size = ft_strlen(node->arg);
	return (1);
}
