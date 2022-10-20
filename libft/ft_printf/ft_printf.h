/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 09:58:49 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:49:57 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../include/libft.h"
# include <stdarg.h>

# define CONV "discoxXfpuU%b"
# define MODS "* #-.+lhLjz"
# define CAPITAL 32

typedef struct s_modifiers
{
	int		plus;
	int		minus;
	int		dot;
	int		hash;
	int		space;
	int		zero;
	int		star;
	int		width;
	int		l;
	int		h;
	int		ld;
	int		j;
	int		z;
	int		capital;
	int		cap_u;
	int		precision;
	int		o_zero;
	int		d_space;
	long	sign;
	int		p_spec;
	int		d_zerominus;
	int		f_prec;
	int		f_zero;
}			t_modifiers;

int			ft_printf(char *format, ...);
int			conversion(va_list args, char *format);
// int			find_letter(char c, char *letters);
int			f_specifier(va_list args, t_modifiers *mods);
int			p_specifier(va_list args, t_modifiers *mods);
int			u_specifier(va_list args, t_modifiers *mods);
int			c_specifier(va_list args, t_modifiers *mods);
int			d_specifier(va_list args, t_modifiers *mods);
int			s_specifier(va_list args, t_modifiers *mods);
int			o_specifier(va_list args, t_modifiers *mods);
int			x_specifier(va_list args, t_modifiers *mods);
int			per_specifier(va_list args, t_modifiers *mods);
int			b_specifier(va_list args, t_modifiers *mods);
char		*l_length(va_list args, char *format, t_modifiers *mods);
char		*h_length(va_list args, char *format, t_modifiers *mods);
char		*ld_length(va_list args, char *format, t_modifiers *mods);
char		*check_modifiers(char *format, t_modifiers *mods, va_list args);
char		*dot(va_list args, char *format, t_modifiers *mods);
char		*star(va_list args, char *format, t_modifiers *mods);
char		*minus(va_list args, char *format, t_modifiers *mods);
char		*plus(va_list args, char *format, t_modifiers *mods);
char		*space(va_list args, char *format, t_modifiers *mods);
char		*hashtag(va_list args, char *format, t_modifiers *mods);
char		*zero(va_list args, char *format, t_modifiers *mods);
char		*cap_x(va_list args, char *format, t_modifiers *mods);
char		*width(va_list args, char *format, t_modifiers *mods);
char		*j_flag(va_list args, char *format, t_modifiers *mods);
char		*z_flag(va_list args, char *format, t_modifiers *mods);
char		*type_cast(unsigned long long num, t_modifiers *mods, int base);
char		*type_cast_int(long long int num, t_modifiers *mods);
char		*type_cast_double(long double num, t_modifiers *mods);
char		*treat_precis(char *str, t_modifiers *mods, int len, long long num);
char		*treat_width(char *str, t_modifiers *mods, int len);
char		*check_infinity(double num, t_modifiers *mods);
char		*apply_sign(char *string, t_modifiers *mods, long long num);
char		*treat_mods(char *str, t_modifiers *mods, int count, long long num);
t_modifiers	*init_struct(t_modifiers *mods);
char		*check_edges(t_modifiers *mods, char *format, long long num);
char		*treat_zerox(char *string, t_modifiers *mods, long long num);
char		*do_nothing(va_list args, char *format, t_modifiers *mods);
int			do_nothing_conv(va_list args, t_modifiers *mods);

typedef int			(*t_spec)(va_list args, t_modifiers *mods);
typedef char		*(*t_mods)(va_list args, char *format, t_modifiers *mods);

static const t_mods	g_mods[15] = {
	star,
	space,
	hashtag,
	minus,
	dot,
	plus,
	l_length,
	h_length,
	ld_length,
	j_flag,
	z_flag,
	do_nothing
};

static const t_spec	g_specif[15] = {
	d_specifier,
	d_specifier,
	s_specifier,
	c_specifier,
	o_specifier,
	x_specifier,
	x_specifier,
	f_specifier,
	p_specifier,
	u_specifier,
	u_specifier,
	per_specifier,
	b_specifier,
	do_nothing_conv
};
#endif
