/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:41:48 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/17 23:10:02 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALISING_H
# define INITIALISING_H
//# include "ast.h"

typedef struct s_quotes
{
	int		s_quote;
	int		d_quote;
	int		closed;
}			t_quotes;

typedef struct s_pars
{
	int		len;
	char	**parsed;
	char	*trimmed;
	char	*last_token_str;
}			t_pars;

typedef struct s_word
{
	int		len;
	int		k;
	int		i;
	int		total;
	int		type;
	int		redir;
	int		redir_way;
	char	*file;
}			t_word;

void		initialise_structs(t_quotes *quotes, t_word *values, char *input);
//char		**initialize_and_set_builtins(void);
void		set_pars_struct(t_pars *pars, char *input);
void		set_start_values(t_ast ***tree, char *buf, int *rb);
void		init_tree(t_ast ***tree, size_t size);

#endif
