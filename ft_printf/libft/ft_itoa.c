/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 20:45:59 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 14:34:52 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_itoa(intmax_t n)
{
	char	*num;
	size_t	i;

	i = numlen(n);
	if (!(num = (char *)ft_memalloc(i + 1)))
		return (0);
	if (n < 0)
		num[0] = '-';
	num[i--] = 0;
	if (!n)
		num[i] = '0';
	while (n)
	{
		if (n < 0)
			num[i--] = (n % 10) * -1 + 48;
		else
			num[i--] = n % 10 + 48;
		n /= 10;
	}
	return (num);
}
