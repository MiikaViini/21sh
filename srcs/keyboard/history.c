/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:45:45 by spuustin          #+#    #+#             */
/*   Updated: 2023/01/02 18:58:24 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	history_command(t_term *t)
{
	int		i;

	i = 0;
	while (t->history[i])
	{
		ft_printf("%4d %s", i, t->history[i]);
		write(1, "\n", 1);
		i++;
	}
}

void	write_history_to_file(t_term *t)
{
	int		cpy;
	int		fd;

	fd = open(t->history_file, O_WRONLY | O_TRUNC);
	if (fd)
	{
		cpy = 0;
		if (t->history_size > MAX_HISTORY)
			cpy = t->history_size % MAX_HISTORY;
		while (cpy < t->history_size)
		{
			ft_putendl_fd((char *)t->history[cpy], fd);
			cpy++;
		}
		close(fd);
	}
	//ft_strdel(&t->history_file);
	//ft_free_array(t->history);
}

/*
	TEST: getcwd failure
*/
static char	*get_file(void)
{
	char	cwd[MAX_PATH];
	char	*home;
	char	*file;

	home = getenv("HOME");
	if (home)
		return (ft_strjoin(home, "/.42sh_history"));
	file = getcwd(cwd, sizeof(cwd));
	return (ft_strjoin(file, "/.42sh_history"));
}

static void	count_history(t_term *t)
{
	int		fd;
	char	*line;
	int		size;

	fd = open(t->history_file, O_RDONLY | O_CREAT, 420);
	size = 0;
	if (fd)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			size++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
	}
	t->history_size = size;
}

void	history_to_array(t_term *t)
{
	char	*line;
	int		fd;
	int		i;

	t->history_file = get_file();
	count_history(t);
	t->history = (char **)malloc(sizeof(char *) * (t->history_size + 1));
	ft_bzero(t->history, t->history_size + 1);
	i = 0;
	fd = open(t->history_file, O_RDONLY | O_CREAT, 420);
	if (fd)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			t->history[i] = ft_strdup(line);
			i++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
		t->history[i] = NULL;
		t->history_size = i;
	}
}
