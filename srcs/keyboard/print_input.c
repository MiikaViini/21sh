/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:14:38 by spuustin          #+#    #+#             */
/*   Updated: 2022/12/21 21:32:12 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It returns the length of the line at the given row
 *
 * @param t the terminal structure
 * @param row the row of the cursor
 *
 * @return The length of the line.
 */
static int	line_len(t_term *t, ssize_t row)
{
	int	len;

	if (t->nl_addr[row + 1])
		len = (int)(t->nl_addr[row + 1] - t->nl_addr[row]);
	else
		len = (int)(&t->inp[t->bytes] - t->nl_addr[row]);
	return (len);
}

/**
 * It transfers the changes
 * made to the cursor position to the terminal structure
 *
 * @param t The terminal structure.
 * @param row the row of the cursor
 * @param col the column of the cursor
 * @param mode 1 = set cursor position, 0 = get cursor position
 */
static void	transfer_changes(t_term *t, ssize_t row, ssize_t col, int mode)
{
	if (mode == 1)
	{
		t->c_row = row;
		t->c_col = col;
	}
}

/**
 * It prints the input buffer to the terminal, and then moves the cursor
 * to the correct position
 *
 * @param t the term structure
 * @param row the row of the cursor
 * @param mode 0 - normal, 1 - insert, 2 - delete
 */
void	ft_print_input(t_term *t, ssize_t row, int mode)
{
	int		len;
	ssize_t	col;

	col = 0;
	while (t->nl_addr[row])
	{
		len = line_len(t, row);
		if (ft_is_prompt_line(t, row))
		{
			if (!row)
				col = write(STDOUT_FILENO, SHELL_PROMPT, t->prompt_len);
			else
				col = write(STDOUT_FILENO, OPEN_QUOTE, t->m_prompt_len);
		}
		else
			col = 0;
		col += write(STDOUT_FILENO, t->nl_addr[row], len);
		if (!t->nl_addr[row + 1])
			break ;
		row++;
	}
	transfer_changes(t, row, col, mode);
}
