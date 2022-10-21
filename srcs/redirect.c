/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:24:49 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/21 14:53:07 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	redirect(char **input, t_env *env)
{
	int	fd;
	char *temp;
	char *temparg[100] = {"/bin/ls", "-l"};
	int pid;

	// if (stat(exec, &stat_) != -1 && !S_ISREG(stat_.st_mode))
	// 	return (1);
	temp = input[0];
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		if (ft_strcmp(input[1], ">>") == 0)
			fd = open(input[2], O_WRONLY | O_CREAT, 0777, O_APPEND);
		else
			fd = open(input[2], O_CREAT, 0777 | O_WRONLY);
		dup2(fd, STDOUT_FILENO);
		if (execve("/bin/ls", temparg, env->env) == -1)
		{
			error_print(temp, NULL, E_EXE);
			exit(EXIT_FAILURE);
		}
	}
	wait(&pid);
	return (0);
}
