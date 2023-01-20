/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:16:42 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/20 09:33:32 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

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
# define E_AMB "ambigous redirect"
# define E_BFD "Bad file descriptor"
# define E_SYNERR "syntax error near unexpected token"
# define E_INP "unexpected error with input"
# define E_NOTERM "could not get TERM value"
# define E_TDB "could not access termcap database"
# define E_UKNTERM "uknwown TERM"
# define E_CAP "cannot run capability"
# define E_TCATTR "cannot set terminal parameters"
#endif
