/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjustment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:19:22 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 20:19:54 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		handler_kostyls(t_args *node, t_format *confgr, char *type)
{
	if (*(node->arg) == '0' &&
			(*type == 'd' || *type == 'u' || *type == 'x' ||
				*type == 'X' || *type == 'o' || *type == 'p'))
	{
		if (*type == 'o' && confgr->f_diez)
			*(node->arg) = 0;
		if (!(confgr->p_prec))
			*(node->arg) = 0;
		if (*type == 'x' || *type == 'X')
			*type = 0;
	}
}

static void		handler_sign(t_args *node, t_format *confgr, char type,\
																char *sign)
{
	*sign = 0;
	if (*(node->arg) == '-')
	{
		*sign = '-';
		ft_memmove(node->arg, node->arg + 1, ft_strlen(node->arg));
		(node->arg)[ft_strlen(node->arg)] = 0;
	}
	else if (confgr->f_plus == 1 && type == 'd')
		*sign = '+';
	else if (confgr->f_space == 1 && type == 'd')
		*sign = ' ';
}

static _Bool	handler_apostr(t_args *node, char type)
{
	int		i;
	int		max;

	i = 0;
	if (type == 'd' || type == 'u')
		i = ft_strlen(node->arg) - 1;
	else
		while ((node->arg)[i + 1] != '.' && (node->arg)[i + 1] != 0)
			i++;
	max = i;
	while (i-- + 1)
	{
		if (!((max - i + 1) % 3) && i > 0)
		{
			if (!(node->arg = (char*)ft_realloc_my(node->arg,\
									(ft_strlen(node->arg) + 2) * sizeof(char))))
				return (0);
			ft_memmove(&(node->arg)[i + 1], &(node->arg)[i],\
											ft_strlen(&(node->arg[i])));
			(node->arg)[i] = ',';
		}
	}
	return (1);
}

_Bool			adjustment(t_args *node, t_format *confgr, char type)
{
	char	filler;
	char	sign;

	filler = ' ';
	if (confgr->f_fill == 1)
		filler = '0';
	handler_kostyls(node, confgr, &type);
	handler_sign(node, confgr, type, &sign);
	if (confgr->f_apostr && (type == 'd' || type == 'u' || type == 'f'))
		handler_apostr(node, type);
	if (!(precision(node, confgr, type)))
		return (0);
    if (confgr->f_diez == 1 && confgr->f_fill == 0)
		if (!(putprefix(node, confgr, type)))
			return (0);
    if (!(width(node, confgr, filler)))
		return (0);
	if (confgr->f_diez == 1 && confgr->f_fill == 1)
		if (!(putprefix(node, confgr, type)))
			return (0);
	if (sign)
		if (!(putsign(node, confgr, sign)))
			return (0);
    return (1);
}
