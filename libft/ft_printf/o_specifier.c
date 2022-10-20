/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:41:11 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/10 09:57:16 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_mods(t_modifiers *mods, char *string, unsigned long long num)
{
	if (mods->hash && mods->dot && mods->width >= mods->precision)
		mods->o_zero++;
	if (mods->hash && mods->dot && (int)ft_strlen(string) == mods->precision
		&& num)
		mods->precision++;
}

int	o_specifier(va_list args, t_modifiers *mods)
{
	unsigned long long	num;
	char				*string;
	int					count;
	char				*output;

	mods->plus = 0;
	num = va_arg(args, unsigned long long );
	string = type_cast(num, mods, 8);
	set_mods(mods, string, num);
	if (mods->hash == 1 && num && mods->precision < (int)ft_strlen(string)
		&& string[0] != '0')
		output = ft_strjoin("0", string);
	else
		output = ft_strdup(string);
	ft_strdel(&string);
	string = check_edges(mods, output, num);
	ft_strdel(&output);
	output = treat_mods(string, mods, ft_strlen(string), num);
	ft_strdel(&string);
	count = ft_putstrlen(output);
	ft_strdel(&output);
	return (count);
}
