/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 11:05:13 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 11:52:27 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool			type_e(t_args *node, t_format *confgr, va_list args[2],\
																char type)
{
	double		a;

	a = ret_n_pos_float(args, confgr->n_pos);
	if (!(infnan_check(node, a, type == 'e' ? 'f' : 'F')))
		return (0);
	else if (!node->arg)
		get_exp(node, confgr, a, type);
	if (!(adjustment(node, confgr, type)))
		return (0);
	node->size = ft_strlen(node->arg);
	return (1);
}
