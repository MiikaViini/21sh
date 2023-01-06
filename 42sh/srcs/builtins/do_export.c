/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 08:48:51 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/06 10:42:45 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	sweep_input(char *input, int equ_sign)
{
	int	i;

	i = 0;
	equ_sign = check_equalsign(input);
	if (equ_sign)
	{
		//error_print(NULL, "setenv", E_ARGNOTVAL);
		return (1);
	}
	while (input[i] && input[i] != '=')
	{
		if (!is_valid_char(input[i]))
		{
			error_print(NULL, "setenv", E_NOTALNUM);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_validity(char **input)
{
	int	ret;
	//int	equ_sign;
	int	i;

	i = 0;
//	equ_sign = 0;
	ret = 0;
	while (input[++i])
	{
		if ((input[i] && !ft_isalpha(input[i][0]) && input[i][0] != '_'))
		{
			error_print(NULL, "export", E_NOTVAL);
			return (1);
		}
	}
	//ret = sweep_input(input, equ_sign);
	return (ret);
}

static int	get_var_len(char *input)
{
	int	i;
	int	var_len;

	i = -1;
	var_len = 0;
	while (input[++i])
	{
		var_len++;
		if (input[i] == '=')
			break ;
	}
	return (var_len);
}

static int	find_variable(char *input, t_env *env, int *added)
{
	int	var_len;
	int	i;
	int	k;

	k = 0;
	var_len = get_var_len(input);
	i = 0;
	while (env->intr->env[k])
	{
		if (ft_strncmp(env->intr->env[k], input, var_len) == 0
			&& env->intr->env[k][var_len] == '=')
		{
			while(env->env[i])
				i++;
			ft_printf("ju %s\n", env->intr->env[k]);
			env->env[i++] = ft_strdup(env->intr->env[k]);
			ft_strdel(&env->intr->env[k]);
			env->env[i] = NULL;
			*added = 1;
			break ;
		}
		k += 1;
	}
	return (*added);
}

static int	find_env(char *input, t_env *env, int *added, int *k)
{
	int	var_len;
	int	equ;

	equ = 0;
	var_len = get_var_len(input);
	if (find_variable(input, env, added) 
		|| sweep_input(input, equ))
		return (1);
	while (env->env[*k])
	{
		if (ft_strncmp(env->env[*k], input, var_len) == 0
			&& env->env[*k][var_len] == '=')
		{
			ft_strdel(&env->env[*k]);
			env->env[*k] = ft_strdup(input);
			*added = 1;
			break ;
		}
		*k += 1;
	}
	return (*added);
}

int	do_export(char **input, t_env *env)
{
	int		i;
	int		k;
	int		added;

	k = 0;
	i = 0;
	if (check_validity(input))
		return (1);
	while (input[++i])
	{
		k = 0;
		added = 0;
		added = find_env(input[i], env, &added, &k);
		if (!added)
		{
			env->env[k++] = ft_strdup(input[i]);
			env->env[k] = NULL;
		}
	}
	return (0);
}
