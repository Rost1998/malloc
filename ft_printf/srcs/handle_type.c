/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 13:57:28 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/20 17:47:53 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	assign(t_func func_t[128])
{
	func_t['d'] = type_d;
	func_t['D'] = type_d;
	func_t['i'] = type_d;
	func_t['u'] = type_u;
	func_t['U'] = type_u;
	func_t['x'] = type_x;
	func_t['X'] = type_x;
	func_t['o'] = type_o;
	func_t['O'] = type_o;
	func_t['s'] = type_s;
	func_t['S'] = type_s;
	func_t['c'] = type_c;
	func_t['C'] = type_c;
	func_t['p'] = type_p;
	func_t['%'] = percent;
	func_t['f'] = type_f;
	func_t['F'] = type_f;
	func_t['e'] = type_e;
	func_t['E'] = type_e;
	func_t['g'] = type_g;
	func_t['G'] = type_g;
	func_t['b'] = type_b;
	func_t['n'] = type_n;
}

_Bool		handle_type(const char **modf, t_format *confgr, t_args *node,\
														va_list args[2])
{
	_Bool	error;
	t_func	func_t[128];

	error = 1;
	priority(confgr, **modf);
	assign(func_t);
	error = func_t[(int)**modf](node, confgr, args, **modf);
	(*modf)++;
	if (!error)
		return (0);
	return (1);
}
