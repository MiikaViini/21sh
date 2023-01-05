/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:58:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 12:53:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_line_output(char **remain, const int fd)
{
	size_t	index;
	char	*line;

	index = 0;
	if (!remain[fd][index])
		return (NULL);
	while (remain[fd][index] && remain[fd][index] != '\n')
		index++;
	line = ft_strnew(index);
	if (!line)
		return (NULL);
	index = 0;
	while (remain[fd][index] && remain[fd][index] != '\n')
	{
		line[index] = remain[fd][index];
		index++;
	}
	return (line);
}

static char	*ft_get_remain(char *remain)
{
	size_t		index;
	size_t		str_index;
	char		*str;

	index = 0;
	str_index = 0;
	while (remain[index] && remain[index] != '\n')
		index++;
	if (!remain[index])
	{
		ft_strdel(&remain);
		return (NULL);
	}
	str = ft_strnew(ft_strlen(remain) - index);
	if (!str)
		return (NULL);
	index++;
	while (remain[index])
		str[str_index++] = remain[index++];
	ft_strdel(&remain);
	return (str);
}

static int	ft_read_and_join(int fd, char **remain)
{
	int			read_bytes;
	char		buff[BUFF_SIZE + 1];
	char		*temp;

	read_bytes = 1;
	temp = NULL;
	if (!remain[fd])
		remain[fd] = ft_strnew(1);
	while (!ft_strchr(remain[fd], '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFF_SIZE);
		if (read_bytes == -1)
			return (read_bytes);
		buff[read_bytes] = '\0';
		temp = ft_strjoin(remain[fd], buff);
		ft_strdel(&remain[fd]);
		remain[fd] = temp;
	}
	return (read_bytes);
}

int	get_next_line(const int fd, char **line)
{
	static char	*remain[MAX_FD + 1];
	int			reader;

	if (!line || BUFF_SIZE <= 0 || fd < 0 || fd > MAX_FD)
		return (-1);
	reader = ft_read_and_join(fd, remain);
	if (reader < 0)
		return (-1);
	*line = ft_line_output(remain, fd);
	if (!*line && reader > 0)
		return (-1);
	remain[fd] = ft_get_remain(remain[fd]);
	if (reader > 0 && remain[fd] == NULL)
		return (-1);
	return (*line != NULL);
}
