/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:22:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/22 14:53:06 by mviinika         ###   ########.fr       */
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
	int				file_fd;
	int				fd_close;
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
	TOKEN_INTR_VAR,
	TOKEN_ELSE
}			t_tokens;

typedef enum e_nodes
{
	NODE_CMD,
	NODE_PIPE,
	NODE_SEMICOLON,
	NODE_REDIR,
	NODE_INTR_VAR
}			t_nodes;

typedef enum e_redirs
{
	REDIR_TRUNC,
	REDIR_APPEND,
	REDIR_IN,
	REDIR_HERED,
	REDIR_AGGR_IN,
	REDIR_AGGR_OUT,
	REDIR_AGGR_STERR_STOUT
}			t_redirs;

#endif
