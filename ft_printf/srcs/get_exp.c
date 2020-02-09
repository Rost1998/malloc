/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:50:29 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 11:21:13 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static double	go_to_right(t_format *confgr, double a, int *p)
{
	if (a)
		while (rodl(ABSF(a), confgr->p_prec) < 1.0 && --*p)
			a *= 10;
	return (a);
}

static double	go_to_left(t_format *confgr, double a, int *p)
{
	if (a)
		while (rodl(ABSF(a), confgr->p_prec) >= 10.0 && ++*p)
			a /= 10;
	return (a);
}

static _Bool	exp_format_handle(t_args *node, int p, _Bool sign, char type)
{
	int		len;

	len = ft_strlen(node->arg);
	if (!(node->arg = (char*)ft_realloc_my(node->arg, (len + numlen(p) + 4)\
															* sizeof(char))))
		return (0);
	(node->arg)[len++] = type == 'e' ? 'e' : 'E';
	(node->arg)[len++] = sign ? '+' : '-';
	p <= 9 ? (node->arg)[len++] = '0' : 0;
	ft_memcpy(&(node->arg)[len], ft_itoa(p), numlen(p));
	return (1);
}

_Bool			get_exp(t_args *node, t_format *confgr, double a, char type)
{
	_Bool	sign;
	int		p;

	p = 0;
	a = go_to_right(confgr, a, &p);
	a = go_to_left(confgr, a, &p);
	sign = p < 0 ? 0 : 1;
	if (!(node->arg = ft_itoafloat(a, confgr->p_prec)))
		return (0);
	if (!(exp_format_handle(node, p < 0 ? -p : p, sign, type)))
		return (0);
	return (1);
}
