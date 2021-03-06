/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:14:48 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/15 14:06:28 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "shell.h"
#include "env.h"
#include <errno.h>

t_shell	*g_shell;

static void			init_cursor(t_cursor **cursor)
{
	struct winsize	win;

	errno = 0;
	ioctl(0, TIOCGWINSZ, &win);
	if ((*cursor = (t_cursor *)malloc(sizeof(t_cursor))))
	{
		(*cursor)->buff_size = 50;
		(*cursor)->line = ft_strnew((*cursor)->buff_size);
		(*cursor)->l_marge = 3;
		(*cursor)->cur_line = 1;
		(*cursor)->nb_line = 1;
		(*cursor)->r_marge = 3;
		(*cursor)->cur_col = 3;
		(*cursor)->max_col = win.ws_col;
		(*cursor)->beg_select = -1;
		(*cursor)->end_select = -1;
		(*cursor)->str_cpy = NULL;
	}
}

int					init_term(t_cursor **cur)
{
	char			*name;
	struct termios	cur_term;

	errno = 0;
	if ((name = getenvline("TERM")) == NULL)
		return (1);
	if ((tgetent(NULL, name) == ERR))
	{
		free(name);
		return (1);
	}
	free(name);
	init_cursor(cur);
	g_shell->cursor = *cur;
	if (tcgetattr(STDIN_FILENO, &((*cur)->term)) == -1)
		return (1);
	cur_term = (*cur)->term;
	cur_term.c_lflag &= ~(ICANON | ECHO);
	cur_term.c_cc[VMIN] = 1;
	cur_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &cur_term))
		return (1);
	return (0);
}

int					term_dfl(t_cursor *cur)
{
	if (tcgetattr(0, &(cur->term)) == -1)
		return (-1);
	cur->term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &cur->term) == -1)
		return (-1);
	tputs(tgetstr("ve", 0), 1, my_putchar);
	return (0);
}
