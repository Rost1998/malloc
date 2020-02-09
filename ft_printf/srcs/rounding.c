/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 11:31:59 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 11:49:46 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

double		rodl(double a, int prec)
{
	double		r;
	double		cp;

	r = 10.0;
	cp = a;
	if (prec < 0)
		prec = 0;
	while (prec-- + 1)
	{
		cp *= 10;
		r /= 10;
	}
	if ((intmax_t)cp % 10 >= 5)
		a += r;
	return (a);
}

char		*rounding_off(char *res)
{
	int		i;
	int		sign;

	sign = *res == '-' ? 1 : 0;
	i = ft_strlen(res) - 1;
	if (res[i--] >= '5')
	{
		while ((res[i] == '9' || res[i] == '.') && i >= sign)
			if (res[i--] != '.')
				res[i + 1] = '0';
		if (i < sign)
		{
			i = sign == 1 ? 1 : 0;
			if (!(res = (char*)ft_realloc_my(res, (ft_strlen(res) + 2)\
													* sizeof(char))))
				return (0);
			ft_memmove(res + sign + 1, res + sign, ft_strlen(res) - sign);
			*(res + sign) = '0';
		}
		(res[i])++;
	}
	res[ft_strlen(res) - 1] = 0;
	return (res);
}
