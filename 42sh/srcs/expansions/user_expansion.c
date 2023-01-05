/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:45:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/16 12:04:13 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	is_valid_user(char *input, char *name)
{
	if (ft_strcmp(&input[1], name) == 0 && input[0] != '.' && input[1] != '.')
		return (1);
	return (0);
}

int	linux_users(char **path, char *input)
{
	if (LIN)
	{
		*path = passwd_user(input);
		if (path == NULL)
			error_print(input + 1, NULL, E_NOUSER);
		return (-1);
	}
	return (0);
}

char	*user_expansion(char *input)
{
	DIR				*dir;
	struct dirent	*entity;
	char			*path;

	if (linux_users(&path, input) == -1)
		return (path);
	dir = opendir("/Users");
	path = NULL;
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	while (entity != NULL)
	{
		if (is_valid_user(input, entity->d_name))
		{
			path = ft_strjoin("/Users/", &input[1]);
			closedir(dir);
			return (path);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	path = passwd_user(input);
	return (path);
}
