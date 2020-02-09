/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_sign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:19:33 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/20 15:53:43 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool	putsign(t_args *node, t_format *confgr, char sign)
{
	int		i;

	i = 0;
	if ((int)ft_strlen(node->arg) == confgr->w_width)
	{
		if (confgr->f_alignment == 0)
			while (!ft_isdigit((node->arg)[i + 1]))
				i++;
		else
			ft_memmove(node->arg + 1, node->arg, ft_strlen(node->arg) - 1);
	}
	else
	{
		if (!(node->arg = (char*)ft_realloc_my(node->arg,\
								(ft_strlen(node->arg) + 2) * sizeof(char))))
			return (0);
		ft_memmove(node->arg + 1, node->arg, ft_strlen(node->arg));
	}
	(node->arg)[i] = sign;
	return (1);
}
