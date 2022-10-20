/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:55:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/18 13:24:58 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
