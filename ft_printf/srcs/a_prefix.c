/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_prefix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:49:07 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/16 19:23:48 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static _Bool	widthyet(t_args *node, char type)
{
	int		i;
	int		diff;

	i = 0;
	diff = (type == 'x' || type == 'X' || type == 'p') ? 2 : 1;
	while ((node->arg)[i] == '0')
		i++;
	while (i++ < diff)
	{
		if (!(node->arg = (char*)ft_realloc_my(node->arg,\
								(ft_strlen(node->arg) + 2) * sizeof(char))))
			return (0);
        ft_memmove(node->arg + 1, node->arg, ft_strlen(node->arg));
	}
	if (type == 'o')
		ft_memcpy(node->arg, "0", 1);
	else if (type == 'x' || type == 'p')
		ft_memcpy(node->arg, "0x", 2);
	else if (type == 'X')
		ft_memcpy(node->arg, "0X", 2);
	return (1);
}

static _Bool	onlyprecision(t_args *node, char type)
{
	if (!(node->arg = ft_realloc_my(node->arg, (ft_strlen(node->arg) + 3)\
												* sizeof(char))))
		return (0);
    if (type == 'o' && *(node->arg) != '0' &&
			ft_memmove(node->arg + 1, node->arg, ft_strlen(node->arg)))
		ft_memcpy(node->arg, "0", 1);
	else if ((type == 'x' || type == 'p') && ft_memmove(node->arg + 2,\
									node->arg, ft_strlen(node->arg)))
		ft_memcpy(node->arg, "0x", 2);
	else if (type == 'X' && ft_memmove(node->arg + 2, node->arg,\
												ft_strlen(node->arg)))
		ft_memcpy(node->arg, "0X", 2);
	return (1);
}

_Bool			putprefix(t_args *node, t_format *confgr, char type)
{
	if ((int)ft_strlen(node->arg) == confgr->w_width)
	{
		if (!widthyet(node, type))
			return (0);
	}
	else
	{
		if (!(onlyprecision(node, type)))
			return (0);
    }
	return (1);
}
