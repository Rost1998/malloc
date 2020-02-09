/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_precision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 11:35:15 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/20 13:54:11 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static _Bool	handler_num(t_args *node, t_format *confgr)
{
	int		diff;

	diff = confgr->p_prec - ft_strlen(node->arg);
	if (diff > 0)
	{
		if (!(node->arg = (char*)ft_realloc_my(node->arg,\
						ft_strlen(node->arg) + diff + 1)))
			return (0);
		ft_memmove(node->arg + diff, node->arg, ft_strlen(node->arg));
		while (--diff + 1)
			(node->arg)[diff] = '0';
	}
	return (1);
}

static size_t	prec_s_analyzer(char *str)
{
	char			*tmp;
	size_t			i;
	unsigned char	symb;

	i = 0;
	tmp = 0;
	while (*str)
	{
		symb = *((unsigned char*)str);
		if (symb >= 0xC0 && (tmp = str))
			i = 1 + (symb >= 0xC0) + (symb >= 0xE0) + (symb >= 0xF0);
		str++;
	}
	return (i > ft_strlen(tmp) ? ft_strlen(tmp) : 0);
}

static _Bool	handler_s(t_args *node, t_format *confgr)
{
	size_t	len;

	len = ft_strlen(node->arg);
	if (ft_strlen(node->arg) > (size_t)confgr->p_prec)
	{
		(node->arg)[confgr->p_prec] = 0;
		len = confgr->p_prec - prec_s_analyzer(node->arg);
		node->arg = ft_realloc_my(node->arg, len + 1);
	}
	if (!(node->arg))
		return (0);
	(node->arg)[len] = 0;
	return (1);
}

_Bool			precision(t_args *node, t_format *confgr, char type)
{
	if (type == 'd' || type == 'u' || type == 'x' || type == 'X' ||
			type == 'b' || type == 'o' || type == 'p')
		if (!(handler_num(node, confgr)))
			return (0);
	if (type == 's' && confgr->p_prec >= 0)
		if (!(handler_s(node, confgr)))
			return (0);
	return (1);
}
