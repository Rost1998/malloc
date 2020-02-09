/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:52:24 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 10:49:46 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool	percent(t_args *node, t_format *confgr, va_list args[2], char type)
{
	(void)args[0];
	if (!(node->arg = (char*)ft_memalloc(2 * sizeof(char))))
		return (0);
	*(node->arg) = '%';
	if (!adjustment(node, confgr, type))
		return (0);
	node->size = ft_strlen(node->arg);
	return (1);
}
