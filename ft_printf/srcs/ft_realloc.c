/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:58:40 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/07 12:09:27 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_realloc_my(void *ptr, size_t newsize)
{
	void	*new;
	size_t	len;

	if (!(new = ft_memalloc(newsize)))
		return (0);
	if ((len = ft_strlen((char*)ptr)) < newsize)
		ft_memmove(new, ptr, len);
	else
		ft_memmove(new, ptr, newsize);
	free(ptr);
	return (new);
}
