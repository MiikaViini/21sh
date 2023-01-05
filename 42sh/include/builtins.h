/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:22:36 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/03 14:23:15 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "ft_21sh.h"



typedef struct s_intr
{
	char	**env;
	char	**path;
	char	*terminal;
	int 	i;
}			t_intr;

typedef struct s_env
{
	char			**env;
	char			**path;
	char			*terminal;
	struct s_intr 	*intr;
}					t_env;

typedef int					(*t_builtins)(char **input, t_env *env);

int			do_cd(char **input, t_env *env);
int			do_echo(char **input, t_env *env);
int			do_env(char **input, t_env *env);
int			do_exit(char **input, t_env *env);
int			do_export(char **input, t_env *env);
int			do_unsetenv(char **input, t_env *env);
int			do_set(char **input, t_env *env);

static const t_builtins		g_builtins[7] = {
	do_echo,
	do_cd,
	do_export,
	do_unsetenv,
	do_exit,
	do_set,
	NULL
};

#endif
