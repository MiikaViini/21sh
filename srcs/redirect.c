/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:24:49 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/24 15:10:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	redirect(t_pars *pars, t_env *env)
{

	(void)env;
	if (ft_strcmp(pars->parsed[1], ">>") == 0)
		pars->fd = open(pars->parsed[2], O_WRONLY | O_CREAT, 0777, O_APPEND);
	else
		pars->fd = open(pars->parsed[2], O_CREAT, 0777 | O_WRONLY);
	pars->parsed[1] = NULL;
	dup2(pars->fd, STDOUT_FILENO);
	return (0);
}
