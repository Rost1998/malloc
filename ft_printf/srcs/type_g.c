/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 12:11:47 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 18:48:43 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		kostyl_dellzero(char *tmp)
{
	int		i;
	int		len_exp;

	i = -1;
	len_exp = ft_strlen(tmp);
	while (tmp[i] == '0' || tmp[i] == '.')
		--i;
	ft_memmove(&tmp[++i], tmp, len_exp);
	tmp[i + len_exp] = 0;
}

static void		dellzero(t_args *node)
{
	char	*tmp;
	_Bool	dot_exist;

	dot_exist = 0;
	if ((node->arg)[0] == '0' && (node->arg)[1] == 0)
		return ;
	tmp = node->arg;
	while (*tmp != 'e' && *tmp != 'E' && *tmp)
		if (*tmp++ == '.')
			dot_exist = 1;
	if (!(*tmp) && dot_exist)
	{
		while (*--tmp == '0')
			*tmp = 0;
		if (*tmp == '.')
			*tmp = 0;
	}
	else if (*tmp)
		kostyl_dellzero(tmp);
}

static int		floatlen(double a)
{
	int		i;

	i = 0;
	if (ABSF(a) >= 1.0)
		while ((int)ABSF(a) / 10 && ++i)
			a /= 10.0;
	else if (a)
		while (!((int)a) && --i)
			a *= 10.0;
	return (i);
}

_Bool			type_g(t_args *node, t_format *confgr, va_list args[2],\
																char type)
{
	int		i;
	double	a;

	a = 0;
	a = ret_n_pos_float(args, confgr->n_pos);
	if (!infnan_check(node, a, type == 'g' ? 'f' : 'F'))
		return (0);
	else if (!node->arg)
	{
		i = floatlen(a);
		if (i && (i < -4 || i >= confgr->p_prec))
		{
			--(confgr->p_prec);
			get_exp(node, confgr, a, type == 'g' ? 'e' : 'E');
		}
		else
			node->arg = ft_itoafloat(a, confgr->p_prec - i - 1);
		dellzero(node);
		if (!(adjustment(node, confgr, type)))
			return (0);
	}
	node->size = ft_strlen(node->arg);
	return (1);
}
