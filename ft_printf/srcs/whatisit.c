/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismodsize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:04:45 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/20 18:50:12 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

_Bool	isflags(char c)
{
	if (c == '-' || c == '+' ||
		c == ' ' || c == '#' ||
		c == '0' || c == '\'')
		return (1);
	return (0);
}

_Bool	iswidth(char c)
{
	if ((c >= '1' && c <= '9') || c == '*')
		return (1);
	return (0);
}

_Bool	isprecision(char c)
{
	if (c == '.')
		return (1);
	return (0);
}

_Bool	ismodsize(char c)
{
	if (c == 'l' || c == 'h' ||
		c == 'j' || c == 'z')
		return (1);
	return (0);
}

_Bool	istype(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == '%' ||
		c == 'x' || c == 'X' || c == 'o' || c == 'O' ||
		c == 'u' || c == 'U' || c == 'c' || c == 'C' ||
		c == 's' || c == 'S' || c == 'p' || c == 'b' ||
		c == 'f' || c == 'F' || c == 'e' || c == 'E' ||
		c == 'g' || c == 'G' || c == 'n')
		return (1);
	return (0);
}
