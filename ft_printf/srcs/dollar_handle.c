/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:29:21 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 10:36:31 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool		isdollar(const char *modf)
{
	if (ft_isdigit(*modf) && *(modf + 1) == '$')
		return (1);
	return (0);
}

int			check_n_pos(const char **modf)
{
	int		n;

	n = ft_atoi(modf);
	(*modf)++;
	return (n);
}

uintmax_t	ret_n_pos_ints(va_list args[2], int n)
{
	uintmax_t	value;

	value = 0;
	if (n)
	{
		va_copy(args[1], args[0]);
		while (n-- > 0)
			value = va_arg(args[1], uintmax_t);
	}
	else
		value = va_arg(args[1], uintmax_t);
	return (value);
}

double		ret_n_pos_float(va_list args[2], int n)
{
	double	value;

	value = 0;
	if (n)
	{
		va_copy(args[1], args[0]);
		while (n-- > 0)
			value = va_arg(args[1], double);
	}
	else
		value = va_arg(args[1], double);
	return (value);
}
