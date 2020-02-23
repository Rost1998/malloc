/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:02:56 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/17 17:25:48 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	first_macros(char *chars, int numb, int bytes, int *a)
{
	int		n;

	n = 8 - (bytes + 1);
	while (n--)
	{
		chars[numb] <<= 1;
		chars[numb] |= (*a & 1);
		*a >>= 1;
	}
	chars[numb] <<= (bytes + 1);
	bytes = ft_pow(2, bytes) - 1;
	chars[numb] |= bytes;
	chars[numb] = ft_revbits(chars[numb]);
}

static void	sec_macros(char *chars, int numb, int *a)
{
	int		n;

	n = 6;
	while (n--)
	{
		chars[numb] <<= 1;
		chars[numb] |= (*a & 1);
		*a >>= 1;
	}
	chars[numb] <<= 2;
	chars[numb] |= 1;
	chars[numb] = ft_revbits(chars[numb]);
}

static void	fillbyte(char *chars, int numb, int a)
{
	int		bytes;

	bytes = numb;
	while (--numb + 1)
	{
		if (numb)
			sec_macros(chars, numb, &a);
		else
			first_macros(chars, numb, bytes, &a);
	}
}

int			ft_putwchar(wchar_t c, char *chars)
{
	int		num_byte;
	int		a;

	a = (int)c;
	num_byte = 1 + (a >= 0x80) + (a >= 0x800) + (a >= 0x10000);
	if (num_byte == 1)
		chars[0] = (unsigned char)a;
	else
		fillbyte(chars, num_byte, a);
	return (num_byte);
}
