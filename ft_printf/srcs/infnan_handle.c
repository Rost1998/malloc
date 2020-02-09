/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 12:56:55 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 12:43:30 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool		nan_handle(t_args *node, char type)
{
	if (!(node->arg = (char*)ft_memalloc(4 * sizeof(char))))
		return (0);
	if (type == 'f')
		ft_memcpy(node->arg, "nan", 3);
	else
		ft_memcpy(node->arg, "NAN", 3);
	return (1);
}

_Bool		inf_handle(t_args *node, double a, char type)
{
	int		diff;

	diff = 0;
	if (!(node->arg = (char*)ft_memalloc(5 * sizeof(char))))
		return (0);
	if (a == -1.0 / 0.0 && (diff = 1))
		*(node->arg) = '-';
	if (type == 'f')
		ft_memcpy(node->arg + diff, "inf", 3);
	else
		ft_memcpy(node->arg + diff, "INF", 3);
	return (1);
}

_Bool		infnan_check(t_args *node, double a, char type)
{
	if (a != a)
	{
		if (!nan_handle(node, type))
			return (0);
	}
	else if (a == 1.0 / 0.0 || a == -1.0 / 0.0)
	{
		if (!inf_handle(node, a, type))
			return (0);
	}
	return (1);
}
