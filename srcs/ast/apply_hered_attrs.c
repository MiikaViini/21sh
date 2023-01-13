/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_hered_attrs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:31:48 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/13 16:13:12 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// void ft_heredoc(int fd, t_ast *node, t_tlist ***tokens)
// {
// 	int	i;

// 	i = 0;
// 	(void)node;
// 	(void)fd;
// 	while((**tokens))
// 	{
// 		ft_printf("%s", (**tokens)->str);
// 		(**tokens) = (**tokens)->next;
// 	}
// 	exit(1);
// }

// void apply_hered_attrs(t_ast *node, t_tlist ***tokens)
// {
// 	int	fd;

// 	fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd)
// 		ft_heredoc(fd, node, tokens);
// }
