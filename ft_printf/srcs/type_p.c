/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:35:26 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 10:42:11 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool	type_p(t_args *node, t_format *confgr, va_list args[2], char type)
{
	size_t		ptr;

	ptr = (size_t)ret_n_pos_ints(args, confgr->n_pos);
	if (!(node->arg = ft_itoa_base(ptr, 16, 'x')))
		return (0);
    confgr->f_diez = 1;
	if (!(adjustment(node, confgr, type)))
		return (0);
    node->size = ft_strlen(node->arg);
	return (1);
}
