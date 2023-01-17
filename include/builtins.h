/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:22:36 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/17 23:08:50 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
//# include "ft_21sh.h"

typedef struct s_env
{
	char	**env;
	char	**path;
	char	*terminal;
}			t_env;

typedef int					(*t_builtins)(char **input, t_env *env);

int			do_cd(char **input, t_env *env);
int			do_echo(char **input, t_env *env);
int			do_env(char **input, t_env *env);
int			do_exit(char **input, t_env *env);
int			do_setenv(char **input, t_env *env);
int			do_unsetenv(char **input, t_env *env);

static const t_builtins		g_builtins[7] = {
	do_echo,
	do_cd,
	do_setenv,
	do_unsetenv,
	do_env,
	do_exit,
	NULL
};

#endif
