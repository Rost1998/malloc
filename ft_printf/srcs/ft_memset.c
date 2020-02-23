/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:26:25 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/13 14:18:14 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int		*st;

	st = b;
	while (len--)
		*(unsigned char*)b++ = (unsigned char)c;
	return (st);
}
