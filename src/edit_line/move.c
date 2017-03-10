/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:06:39 by acottier          #+#    #+#             */
/*   Updated: 2017/03/07 13:23:23 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

void	right(t_cursor *cursor, t_hist **hist)
{
	(void)hist;
	if (cursor->r_marge >= cursor->cur_col + 1)
	{
		(cursor->cur_col)++;
		tputs(tgetstr("nd", 0), 1, my_putchar);
	}
	//else if (cursor->nb_line > cursor->cur_line)
	//{
	//	(cursor->cur_line)++;
	//	tputs(tgetstr("do", 0), 1, my_putchar);
		set_marge(cursor);
	//	while (cursor->cur_col > cursor->l_marge)
	//	{
	//		(cursor->cur_col)--;
	//		tputs(tgetstr("le", 0), 1, my_putchar);
	//	}
	//}
	//printf("line = %d\ncol = %d\n", cursor->cur_line, cursor->cur_col);
}

void	left(t_cursor *cursor, t_hist **hist)
{
	(void)hist;
	if (cursor->l_marge < cursor->cur_col)
	{
		(cursor->cur_col)--;
		tputs(tgetstr("le", 0), 1, my_putchar);
	}
	else if (cursor->cur_line > 1)
	{
		(cursor->cur_line)--;
		tputs(tgetstr("up", 0), 1, my_putchar);
		set_marge(cursor);
		while (cursor->cur_col < cursor->max_col)
		{
			(cursor->cur_col)++;
			tputs(tgetstr("nd", 0), 1, my_putchar);
		}
	}
}

void	next_word(t_cursor *cursor, t_hist **hist)
{
	int			i;
	int			line;
	int			col;

	(void)hist;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	while (cursor->line[i] && cursor->line[i] != ' ')
		i++;
	while (cursor->line[i] && cursor->line[i] == ' ')
		i++;
	set_pos(cursor, i, &line, &col);
	go_pos(cursor, line, col);
	set_marge(cursor);
}

void	prev_word(t_cursor *cursor, t_hist **hist)
{
	int			i;
	int			line;
	int			col;

	(void)hist;
	i = cursor->cur_col - 3 + cursor->max_col * (cursor->cur_line - 1);
	while (i > 0 && cursor->line[i] != ' ')
		i--;
	while (i > 0 && cursor->line[i] == ' ')
		i--;
	set_pos(cursor, i, &line, &col);
	go_pos(cursor, line, col);
	set_marge(cursor);
}
