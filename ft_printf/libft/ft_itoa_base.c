/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:30:53 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/11 15:02:38 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_numlen(uintmax_t a, unsigned base)
{
	int		i;

	if (!a)
		return (1);
	i = 0;
	while (a)
	{
		a /= base;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(uintmax_t a, unsigned base, char type)
{
	char	*res;
	char	*symbols;
	int		i;

	symbols = "0123456789abcdef";
	if (type == 'X')
		symbols = "0123456789ABCDEF";
	if (!(res = (char*)ft_memalloc((ft_numlen(a, base) + 1) * sizeof(char))))
		return (0);
	if (!a)
		*res = '0';
	i = 0;
	while (a)
	{
		res[i++] = symbols[a % base];
		a /= base;
	}
	ft_revarr(res);
	return (res);
}
