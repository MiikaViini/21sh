/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:14:35 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/15 14:18:58 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// Checks if directory exists, can be executed or is a directory.
// param input is directory to be entered
static int	check_access(char *input)
{
	int			ret;
	struct stat	buf;

	stat(input, &buf);
	ret = 0;
	if (chdir(input) == -1)
	{

		if (access(input, F_OK) && !S_ISDIR(buf.st_mode))
		{
			error_print(input, "cd", E_NOEX);
			ret = 1;
		}
		else if (S_ISDIR(buf.st_mode) && access(input, X_OK))
		{
			error_print(input, "cd", E_NOPERM);
			ret = 1;
		}
		else
			error_print(input, "cd", E_NODIR);
		ret = 1;
	}
	return (ret);
}

//Prints error messages if HOME or OLDPWD doesnt exist in env list
static int	check_env_var(char *input, char **env)
{
	if ((!*env && !input) || (!*env && ft_strncmp(input, "--", 2) == 0))
	{
		error_print("HOME", "cd", E_NULLVAR);
		return (1);
	}
	else if (!*env && ft_strncmp(input, "-", 1) == 0)
	{
		error_print("OLDPWD", "cd", E_NULLVAR);
		return (1);
	}
	return (0);
}

//Check if HOME or OLDPWD variables are set or not.
static int env_dir(char *input, char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!input || ft_strncmp(input, "--", 2) == 0)
		{
			if (ft_strncmp(env[i], "HOME=", 5) == 0)
				if (!chdir(env[i] + 5))
					break ;
		}
		else if (ft_strncmp(input, "-", 1) == 0)
		{
			if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			{
				ft_putendl(env[i] + 7);
				if (!chdir(env[i] + 7))
					break ;
			}
		}
	}
	if (check_env_var(input, &env[i]))
		return (1);
	return (0);
}

// Execute cd builtin. Tries to access given directory. Does proper checking
// before trying to set it to current working directory.
int	do_cd(char **input, t_env *env)
{
	char	old_cwd[MAX_PATH + 1];
	char	cwd[MAX_PATH + 1];

	ft_memset(old_cwd, '\0', 1025);
	ft_memset(cwd, '\0', 1025);
	getcwd(old_cwd, MAX_PATH);
	if (input[1] && !(ft_strncmp(input[1], "-", 1) == 0)
		&& check_access(input[1]))
		return (1);
	else if (!input[1] || ft_strncmp(input[1], "-", 1) == 0)
	{
		if (env_dir(input[1], env->env))
			return (1);
	}
	getcwd(cwd, MAX_PATH);
	if (cwd[0] == '\0')
		update_env(env->env, input[1], "PWD");
	else
		update_env(env->env, cwd, "PWD");
	update_env(env->env, old_cwd, "OLDPWD");
	return (0);
}
