/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 11:19:31 by rtulchiy          #+#    #+#             */
/*   Updated: 2018/05/31 16:53:26 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <inttypes.h>

# define ABSF(x) ((x) < 0.0 ? -(x) : (x))

typedef struct	s_args
{
	char		*res;
	char		*arg;
	size_t		size;
	int			n;
}				t_args;

typedef struct	s_format
{
	char		f_alignment;
	char		f_plus;
	char		f_diez;
	char		f_space;
	char		f_apostr;
	char		f_fill;
	int			w_width;
	int			p_prec;
	size_t		s_byte;
	int			n_pos;
}				t_format;

typedef	_Bool	(*t_func)\
				(t_args*, t_format*, va_list[2], char);

typedef union	u_dlb
{
	double		dl;
	uint64_t	intdl;
}				t_dlb;

_Bool			get_exp(t_args *node, t_format *confgr, double a, char type);
_Bool			nan_handle(t_args *node, char type);
_Bool			inf_handle(t_args *node, double a, char type);
_Bool			infnan_check(t_args *node, double a, char type);
char			*ft_itoafloat(double num, int prec);
char			*rounding_off(char *res);
double			rodl(double a, int prec);
int				check_n_pos(const char **modf);
uintmax_t		ret_n_pos_ints(va_list args[2], int n);
double			ret_n_pos_float(va_list args[2], int n);
_Bool			isdollar(const char *modf);
void			*ft_memset(void *ptr, int c, size_t len);
void			ft_putmem(char *str, size_t size);
_Bool			percent(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			ft_isdigit(int c);
_Bool			putprefix(t_args *node, t_format *confgr, char type);
_Bool			putsign(t_args *node, t_format *confgr, char sign);
long			ft_pow(long a, int d);
int				ft_printf(const char *format, ...);
int				parser(const char *format, va_list args[2]);
_Bool			handle_main(const char **modf, va_list args[2], t_args *node,\
														t_format *confgr);
void			handle_flags(const char **modf, t_format *confgr);
void			handle_width(const char **modf, t_format *confgr,\
															va_list args[2]);
void			handle_precision(const char **modf, t_format *confgr,\
															va_list args[2]);
void			handle_modfsize(const char **modf, t_format *confgr);
_Bool			handle_type(const char **modf, t_format *confgr, t_args *node,\
														va_list args[2]);
_Bool			type_d(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_u(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_x(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_o(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_s(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_c(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_p(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_f(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_e(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_g(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_b(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			type_n(t_args *node, t_format *confgr, va_list args[2],\
																	char type);
_Bool			isflags(char c);
_Bool			iswidth(char c);
_Bool			isprecision(char c);
_Bool			ismodsize(char c);
_Bool			istype(char c);
_Bool			isfloat_type(char c);
void			*ft_memalloc(size_t size);
void			*ft_realloc_my(void *ptr, size_t newsize);
int				ft_atoi(const char **str);
char			*ft_itoa(intmax_t n);
char			*ft_uitoa(uintmax_t n);
char			*ft_itoa_base(uintmax_t a, unsigned base, char type);
size_t			ft_strlen(const char *str);
void			ft_putstr(const char *str);
_Bool			ft_iswhitespaces(int c);
void			*ft_memmove(void *dst, const void *src, size_t len);
_Bool			adjustment(t_args *node, t_format *confgr, char type);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			prefix(t_args *node, t_format *confgr, char type);
_Bool			precision(t_args *node, t_format *confgr, char type);
_Bool			width(t_args *node, t_format *confgr, char filler);
void			ft_revarr(char *str);
void			priority(t_format *confgr, char type);
int				ft_putwchar(wchar_t c, char *chars);
unsigned char	ft_revbits(unsigned char a);
int				numlen(intmax_t num);

#endif
