/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:36:46 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/06 16:39:22 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_revarr(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i < len)
	{
		tmp = str[i];
		str[i++] = str[len];
		str[len--] = tmp;
	}
}
