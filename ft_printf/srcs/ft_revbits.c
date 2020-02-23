/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revbits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 12:07:27 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/08 15:14:40 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned char	ft_revbits(unsigned char byte)
{
	unsigned char	newbyte;
	int				i;

	newbyte = 0;
	i = 8;
	while (i--)
	{
		newbyte <<= 1;
		newbyte |= (byte & 1);
		byte >>= 1;
	}
	return (newbyte);
}
