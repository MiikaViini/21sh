/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:16:42 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/09 19:45:08 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define E_EXE "error occured during execution"
# define E_NOTF "command not found"
# define E_NOTVAL "variable name must begin with a letter."
# define E_ARGNOTVAL "please enter arguments in format 'name=value'."
# define E_NOTALNUM "variable name must contain alphanumeric characters."
# define E_QUOT "invalid quoting, try again"
# define E_NOEX "no such file or directory"
# define E_NOPERM "permission denied"
# define E_NODIR "is not a directory"
# define E_NULLVAR "not set"
# define E_ISDIR "is a directory"
# define E_NOUSER "no such user or named directory"
# define E_NODIGIT "numeric argument required"
# define E_PIPEFAIL "failed to open with pipe()"
# define E_NOFORK "failed to to fork process"
# define E_SYNERR "syntax error"
# define E_AMB "ambigous redirect"
# define E_BFD "Bad file descriptor"
#endif
