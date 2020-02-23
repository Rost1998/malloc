/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 20:45:59 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 14:35:37 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_numlen(uintmax_t n)
{
	int		i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char		*ft_uitoa(uintmax_t n)
{
	char	*num;
	size_t	i;

	i = ft_numlen(n);
	if (!(num = (char *)ft_memalloc(i + 1)))
		return (0);
	num[i--] = 0;
	if (!n)
		num[i] = '0';
	while (n)
	{
		num[i--] = n % 10 + 48;
		n /= 10;
	}
	return (num);
}
