/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:38:18 by mviinika          #+#    #+#             */
/*   Updated: 2022/12/20 12:41:16 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

char		*dollar_expansion(char *expanded, char *word, char **env, int len);
char		*handle_expansions(char *input, char **env);
int			is_expansion(char *str, int i);
char		*passwd_user(char *input);
char		*tilde_expansion(char *word, char **env, char *expanded);
char		*user_expansion(char *input);

#endif
