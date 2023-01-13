/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_remove_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:17:07 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/10 15:36:46 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_validity(char *input)
{
	int	ret;
	//  int	equ_sign;
	int	i;

	i = -1;
	//equ_sign = 0;
	ret = 0;
	while (input[++i])
	{
		if ((!ft_isalpha(input[0]) && input[0] != '_'))
		{
			error_print(NULL, "setenv", E_NOTVAL);
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

static int	find_env(char *input, t_env *env, int *k)
{
	int	var_len;
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	var_len = get_var_len(input);
	while (env->intr->env[*k])
	{
		if (ft_strncmp(env->intr->env[*k], input, var_len) == 0
			&& env->intr->env[*k][var_len - 1] == '=')
		{
			ft_strdel(&env->intr->env[*k]);
			env->intr->env[*k] = ft_strdup(input);
			ret = 1;
			break ;
		}
		*k += 1;
	}
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], input, var_len) == 0
			&& env->env[i][var_len - 1] == '=')
		{
			ft_strdel(&env->env[i]);
			env->env[i] = ft_strdup(input);
			ret = 1;
			break ;
		}
		i++;
	}
	return (ret);
}

static int	do_set_var(char *input, t_env *env)
{
	int		k;
	int		added;

	k = 0;
	if (check_validity(input))
		return (1);
	added = find_env(input, env, &k);
	if (!added)
	{
		env->intr->env[k++] = ft_strdup(input);
		env->intr->env[k] = NULL;
	}
	return (0);
}

// Expands variables from environment and removes quotes
int	expand_and_remove_quotes(t_ast **tree, t_env *env)
{
	int			i;
	int			k;
	t_quotes	quotes;

	k = 0;
	i = 0;
	initialise_structs(&quotes, NULL, NULL);
	if ((*tree)->type == NODE_INTR_VAR)
	{
		while ((*tree)->variables)
		{
			do_set_var((*tree)->variables->var, env);
			(*tree)->variables = (*tree)->variables->next;
		}
	}
	while ((*tree)->type != NODE_PIPE && (*tree)->cmd[i])
	{
		see_quote(&quotes, (*tree)->cmd[i], k);
		while ((*tree)->cmd[i][k])
		{
			if (is_expansion((*tree)->cmd[i], k) && !quotes.s_quote)
			{
				(*tree)->cmd[i] = handle_expansions((*tree)->cmd[i], env);
				break ;
			}
			(*tree)->cmd[i] = remove_quotes((*tree)->cmd[i]);
			k++;
		}
		k = 0;
		i++;
	}
	return (0);
}
