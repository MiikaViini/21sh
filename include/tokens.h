/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:22:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/15 15:19:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_tlist
{
	int				type;
	char			*str;
	struct s_tlist	*next;
}				t_tlist;

typedef enum e_tokens
{
	TOKEN_WORD,
	TOKEN_SEMICOLON,
	TOKEN_PIPE,
	TOKEN_GT,
	TOKEN_LT,
	TOKEN_AGGR,
	TOKEN_TILDE,
	TOKEN_ELSE
}			t_tokens;

typedef enum e_nodes
{
	NODE_CMD,
	NODE_PIPE,
	NODE_SEMICOLON
}			t_nodes;

#endif
