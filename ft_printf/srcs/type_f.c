/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:50:40 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 12:47:57 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool			type_f(t_args *node, t_format *confgr, va_list args[2],\
																char type)
{
	double		a;

	a = ret_n_pos_float(args, confgr->n_pos);
	if (!(infnan_check(node, a, type)))
		return (0);
	else if (!node->arg && !(node->arg = ft_itoafloat(a, confgr->p_prec)))
		return (0);
	if (!(adjustment(node, confgr, 'f')))
		return (0);
	node->size = ft_strlen(node->arg);
	return (1);
}
