/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_width.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:59:45 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 10:47:14 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool		width(t_args *node, t_format *confgr, char filler)
{
	int		diff;

	if (confgr->w_width > (int)ft_strlen(node->arg))
	{
		diff = confgr->w_width - ft_strlen(node->arg);
		if (!(node->arg = (char*)ft_realloc_my(node->arg,\
							ft_strlen(node->arg) + diff + 1)))
			return (0);
		if (confgr->f_alignment == 0 && ft_memmove(node->arg + diff, node->arg,\
														ft_strlen(node->arg)))
			while (--diff + 1)
				(node->arg)[diff] = filler;
		else if ((diff = confgr->w_width))
			while ((int)ft_strlen(node->arg) <= diff)
				(node->arg)[--diff] = filler;
	}
	return (1);
}
