/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoafloat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:25:23 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 12:47:35 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*ft_itoafloat_integer(double num, int prec)
{
	char		*res;
	size_t		len;
	double		copy_num;
	t_dlb		dlb;

	len = 0;
	copy_num = num;
	while ((int)copy_num != 0 && (++len))
		copy_num /= 10;
	if (!(res = (char*)ft_memalloc((len + 3) * sizeof(char))))
		return (0);
	dlb.dl = num;
	if (((dlb.intdl >> 63) & 0x1) == 0x1 && ++len)
		*res = '-';
	if (rodl(ABSF(num), prec) < 1.0)
		res[len] = '0';
	while (ABSF(num) >= 1.0)
	{
		if (num > 0)
			res[--len] = (uintmax_t)num % 10 + '0';
		else
			res[--len] = (intmax_t)num % 10 * -1 + '0';
		num /= 10;
	}
	return (res);
}

static _Bool	allocate_mem(char **res, char **ap, double num, int prec)
{
	if (!(*res = ft_itoafloat_integer(num, prec)))
		return (0);
	if (!(*ap = ft_memalloc((prec + 3) * sizeof(char))))
		return (0);
	if (!(*res = ft_realloc_my(*res, (ft_strlen(*res) + prec + 3) * sizeof(char))))
		return (0);
	return (1);
}

static double	del_left_border(double num)
{
	double		p;
	uintmax_t	nint;

	if (num < 0.0)
		num *= -1.0;
	p = 1.0;
	nint = (uintmax_t)num;
	while (nint / 10)
	{
		nint /= 10;
		p *= 10.0;
	}
	if (p == 1.0)
		return (0);
	while ((uintmax_t)num / (uintmax_t)p != 1)
		p += p;
	return (p);
}

char			*ft_itoafloat(double num, int prec)
{
	char		*res;
	char		*after_point;
	size_t		i;

	prec < 0 ? (prec = 0) : 0;
	if (!allocate_mem(&res, &after_point, num, prec))
		return (0);
	if (!(i = 0) && prec > 0)
		after_point[i++] = '.';
	while (prec-- + 1)
	{
		if (num > 0)
			num -= del_left_border(num);
		else
			num += del_left_border(num);
		num *= 10;
		if (num > 0)
			after_point[i++] = (uintmax_t)num % 10 + '0';
		else
			after_point[i++] = (intmax_t)num % 10 * -1 + '0';
	}
	ft_memmove(res + ft_strlen(res), after_point, ft_strlen(after_point));
	free(after_point);
	return (rounding_off(res));
}
