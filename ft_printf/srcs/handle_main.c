/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:30:13 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 12:45:51 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool	handle_main(const char **modf, va_list args[2], t_args *node,\
												t_format *confgr)
{
	while (isdollar(*modf))
		confgr->n_pos = check_n_pos(modf);
	while (isflags(**modf))
		handle_flags(modf, confgr);
	while (iswidth(**modf))
		handle_width(modf, confgr, args);
	while (isprecision(**modf))
		handle_precision(modf, confgr, args);
	while (ismodsize(**modf))
		handle_modfsize(modf, confgr);
	if (istype(**modf))
	{
		if (!(handle_type(modf, confgr, node, args)))
			return (0);
    }
	else if (**modf)
	{
		if (!(node->arg = (char*)ft_memalloc(2 * sizeof(char))))
			return (0);
        *(node->arg) = *(*modf)++;
		if (!adjustment(node, confgr, 0))
			return (0);
        node->size = ft_strlen(node->arg);
	}
	return (1);
}
