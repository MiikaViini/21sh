/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_and_set_builtins.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:48:27 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/09 21:00:08 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	**initialize_and_set_builtins(void)
{
	static char	*builtins[7] = {"echo", "cd", "export", \
	"unset", "exit", "set"};

	return (builtins);
}
