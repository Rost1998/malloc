/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:58:39 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/20 21:00:22 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static _Bool	null(t_args *node)
{
	if (!(node->arg = (char*)ft_memalloc(7 * sizeof(char))))
		return (0);
	ft_memcpy(node->arg, "(null)", 6);
	return (1);
}

static _Bool	unicode(t_args *node, wchar_t *text)
{
	int		i;
	char	*tmp;

	if (!text)
		null(node);
	else
	{
		i = 0;
		while (text[i])
			i++;
		if (!(node->arg = (char*)ft_memalloc((i * 4 + 1) * sizeof(char))))
			return (0);
		tmp = node->arg;
		while (*text)
		{
			tmp += ft_putwchar(*text, tmp);
			text++;
		}
	}
	return (1);
}

_Bool			type_s(t_args *node, t_format *confgr, va_list args[2],\
															char type)
{
	int		len;
	char	*text;

	if (type == 's' && confgr->s_byte != sizeof(long))
	{
		if (!(text = (char*)ret_n_pos_ints(args, confgr->n_pos)))
			null(node);
		else
		{
			len = ft_strlen(text);
			if (!(node->arg = (char*)ft_memalloc((len + 1) * sizeof(char*))))
				return (0);
			ft_memcpy(node->arg, text, len);
		}
	}
	else if (type == 'S' || (type == 's' && confgr->s_byte == sizeof(long)))
		if (!(unicode(node, (wchar_t*)ret_n_pos_ints(args, confgr->n_pos))))
			return (0);
	if (!(adjustment(node, confgr, 's')))
		return (0);
	node->size = ft_strlen(node->arg);
	return (1);
}
