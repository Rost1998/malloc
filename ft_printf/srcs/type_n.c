/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 16:53:58 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 11:52:13 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool		type_n(t_args *node, t_format *confgr, va_list args[2],\
															char type)
{
	void	*ptr;

	(void)type;
	ptr = (void*)ret_n_pos_ints(args, confgr->n_pos);
	*((int*)ptr) = node->n;
	return (1);
}
