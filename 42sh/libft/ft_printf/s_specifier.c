/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:39:52 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/08 12:25:55 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	s_specifier(va_list args, t_modifiers *mods)
{
	char	*string;
	int		count;
	char	*output;
	char	*temp;

	string = va_arg(args, char *);
	if (string == NULL)
		output = ft_strdup("(null)");
	else
		output = ft_strdup(string);
	if (mods->precision < 0)
		mods->precision = ft_strlen(output);
	if (mods->dot)
		temp = ft_strndup(output, mods->precision);
	else
		temp = ft_strdup(output);
	ft_strdel(&output);
	output = treat_width(temp, mods, ft_strlen(temp));
	ft_strdel(&temp);
	temp = ft_strdup(output);
	ft_strdel(&output);
	count = ft_putstrlen(temp);
	ft_strdel(&temp);
	return (count);
}
