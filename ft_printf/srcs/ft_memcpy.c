/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:59:27 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/05 16:57:15 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*st_dst;

	st_dst = dst;
	while (n--)
		*(unsigned char*)dst++ = *(unsigned char*)src++;
	return (st_dst);
}
