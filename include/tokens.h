/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:22:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/02 11:09:04 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_tlist
{
	int				type;
	int				to_fd;
	int				from_fd;
	char			*file;
	int				redir_way;
	int				redir_type;
	char			*str;
	struct s_tlist	*next;
}				t_tlist;

typedef enum e_tokens
{
	TOKEN_WORD,
	TOKEN_SEMICOLON,
	TOKEN_PIPE,
	TOKEN_REDIRECT,
	TOKEN_REDI_APPEND,
	TOKEN_AGGR,
	TOKEN_TILDE,
	TOKEN_ELSE
}			t_tokens;

typedef enum e_nodes
{
	NODE_CMD,
	NODE_PIPE,
	NODE_SEMICOLON,
	NODE_REDIR
}			t_nodes;

typedef enum e_redirs
{
	REDIR_TRUNC,
	REDIR_APPEND,
	REDIR_IN,
	REDIR_HERED,
	REDIR_AGGR_IO,
	REDIR_AGGR_IN,
	REDIR_AGGR_OUT
}			t_redirs;

#endif
