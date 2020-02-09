/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 12:37:13 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/21 19:35:28 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static t_format	*cr_confgr(t_format *node_confgr)
{
	if (!(node_confgr))
		if (!(node_confgr = (t_format*)ft_memalloc(sizeof(t_format))))
			return (0);
	node_confgr->f_alignment = 0;
	node_confgr->f_plus = 0;
	node_confgr->f_diez = 0;
	node_confgr->f_space = 0;
	node_confgr->f_apostr = 0;
	node_confgr->f_fill = 0;
	node_confgr->w_width = -1;
	node_confgr->p_prec = -1;
	node_confgr->s_byte = 0;
	node_confgr->n_pos = 0;
	return (node_confgr);
}

static t_args	*cr_node(void)
{
	t_args		*node;

	if (!(node = (t_args*)ft_memalloc(sizeof(t_args))))
		return (0);
	node->arg = 0;
	node->size = 0;
	node->n = 0;
	return (node);
}

static void		print_spec(t_args *node)
{
	if (node->arg)
	{
		write(1, node->arg, node->size);
		node->n += node->size;
		free(node->arg);
		node->arg = 0;
		node->size = 0;
	}
}

static int		freemem(t_args *node, t_format *confgr, int code)
{
	int		n;

	n = node->n;
	if (node->arg)
		free(node->arg);
	free(node);
	free(confgr);
	if (code == -1)
		return (-1);
	return (n);
}

int				parser(const char *format, va_list args[2])
{
	t_args		*node;
	t_format	*confgr;

	if (!(node = cr_node()))
		return (-1);
	confgr = 0;
	while (*format)
	{
		if (*format++ == '%')
		{
			if (!(confgr = cr_confgr(confgr)))
				return (freemem(node, confgr, -1));
            if (!(handle_main(&format, args, node, confgr)))
				return (freemem(node, confgr, -1));
            print_spec(node);
		}
		else
		{
			write(1, (format - 1), 1);
			(node->n)++;
		}
	}
	return (freemem(node, confgr, 1));
}
