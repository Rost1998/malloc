/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:17:13 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 20:05:00 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

_Bool		isfloat_type(char c)
{
	if (c == 'f' || c == 'F' ||
			c == 'a' || c == 'A' ||
			c == 'e' || c == 'E' ||
			c == 'g' || c == 'G')
		return (1);
	return (0);
}

int			numlen(intmax_t num)
{
	int		i;

	i = 0;
	if (num <= 0)
		i++;
	while (num && ++i)
		num /= 10;
	return (i);
}
