/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:36:25 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 12:53:22 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	check_redirs(t_ast *tree, t_env *env)
{
	int	ret;

	ret = 0;
	if (tree->type == NODE_REDIR)
	{
		if (redirection(tree->redirs, &ret, env) == -1)
		{
			free_strarr(env->path);
			return (1);
		}	
	}
	return (0);
}
