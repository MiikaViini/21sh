/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:45:45 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/12 22:08:39 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// reads history from a file, and stores it into t->history array
// our history supports up to 100 lines of command-line calls

void	ft_history_write_to_file(t_term *t)
{
	int		cpy;
	int		fd;

	fd = open(t->history_file, O_WRONLY | O_TRUNC);
	if (fd)
	{
		cpy = 0;
		if (t->history_size > 1024)
			cpy = t->history_size % 1024;
		while (cpy < t->history_size)
		{
			ft_putendl_fd((char *)t->history[cpy], fd);
			cpy++;
		}
		close(fd);
	}
	ft_strdel(&t->history_file);
	ft_free_array(t->history);
}

static char	*get_file(void)
{
	char	cwd[1024];
	char	*home;
	char	*file;

	home = getenv("HOME");
	if (home)
		return (ft_strjoin(home, "/.42sh_history"));
	file = getcwd(cwd, sizeof(cwd));
	return (ft_strjoin(file, "/.42sh_history"));
}

void	get_history(t_term *t)
{
	char	*file;
	char	*line;
	int		fd;
	int		i;

	t->history = (char **)malloc(sizeof(char *) * 101);
	ft_bzero(t->history, 101);
	t->history_file = get_file();
	i = 0;
	fd = open(file, O_RDONLY | O_CREAT, 420);
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

void	print_history(t_term *t)
{
	int		i;

	i = 0;
	while (i < t->history_size)
	{
		ft_printf("%s\n", t->history[i]);
		i++;
	}
}
