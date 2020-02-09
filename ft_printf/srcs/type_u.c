/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:44:46 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 10:42:50 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool	type_u(t_args *node, t_format *confgr, va_list args[2], char type)
{
	uintmax_t	a;

	a = 0;
	if (type == 'U' && confgr->s_byte < sizeof(long))
		confgr->s_byte = sizeof(long);
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
	if (!(node->arg = ft_uitoa(a)))
		return (0);
	if (!(adjustment(node, confgr, 'u')))
		return (0);
	node->size = ft_strlen(node->arg);
	return (1);
}
