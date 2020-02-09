/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 13:41:56 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/20 13:56:44 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	isprec_affect(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' ||
			c == 'u' || c == 'U' || c == 'x' ||
			c == 'o' || c == 'O' || c == 'X' ||
			c == 'b')
		return (1);
	return (0);
}

static char	isdiez_affect(char c)
{
	if (c == 'x' || c == 'a')
		return (16);
	if (c == 'X' || c == 'A')
		return (32);
	if (c == 'o' || c == 'O')
		return (8);
	return (0);
}

void		priority(t_format *confgr, char type)
{
	if (confgr->f_alignment == 1 || confgr->w_width == -1 ||\
			(isprec_affect(type) && confgr->p_prec >= 0))
		confgr->f_fill = 0;
	if (confgr->f_plus == 1)
		confgr->f_space = 0;
	if (!isdiez_affect(type))
		confgr->f_diez = 0;
	if (confgr->w_width == -1)
		confgr->f_alignment = 0;
	if (isfloat_type(type) && confgr->p_prec == -1)
		confgr->p_prec = 6;
	if (!(confgr->s_byte) && !isfloat_type(type))
		confgr->s_byte = sizeof(int);
	else if (!(confgr->s_byte) && isfloat_type(type))
		confgr->s_byte = sizeof(double);
}
