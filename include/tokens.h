/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:22:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/11/03 12:21:58 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum e_tokens
{
	TOKEN_WORD,
	TOKEN_SEMICOLON,
	TOKEN_PIPE,
	TOKEN_GT,
	TOKEN_LT,
	TOKEN_AGGR,
	TOKEN_DOLLAR,
	TOKEN_TILDE
}			t_tokens;

#endif
