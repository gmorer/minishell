/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:14:18 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/06 16:58:28 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void			go_home(t_cursor *cursor)
{
	while (cursor->cur_col > 0)
	{
		cursor->cur_col--;
		tputs(tgetstr("le", 0), 1, my_putchar);
	}
	while (cursor->cur_line > 1)
	{
		cursor->cur_line--;
		tputs(tgetstr("up", 0), 1, my_putchar);
	}
}

void			go_pos(t_cursor *cursor, int line, int col)
{
	go_home(cursor);
	while (cursor->cur_line < line)
	{
		tputs(tgetstr("do", 0), 1, my_putchar);
		cursor->cur_line++;
	}
	while (cursor->cur_col < col)
	{
		tputs(tgetstr("nd", 0), 1, my_putchar);
		cursor->cur_col++;
	}
}
