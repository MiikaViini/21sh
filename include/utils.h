/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:54:41 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/19 15:22:25 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int			check_quotes(char *input);
void		error_print(char *word, char *command, char *e_msg);
int			fork_wrapper(void);
void		get_env(t_env *dest, char **environ, int argc, char **argv);
int			is_operator(char c, t_quotes *quots);
char		*remove_quotes(char *input);
void		see_quote(t_quotes *quots, char *input, int i);
void		update_env(char **env, char *input, char *var);
void		free_all(t_pars *pars, t_ast **tree, char *buf);
void		free_parsed_input(char **p_input);

#endif
