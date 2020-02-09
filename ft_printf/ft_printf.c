/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 16:44:42 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/31 16:45:35 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_printf(const char *format, ...)
{
	va_list	args[2];
	int		ret;

	va_start(args[0], format);
	va_copy(args[1], args[0]);
	ret = parser(format, args);
	va_end(args[0]);
	va_end(args[1]);
	return (ret);
}
