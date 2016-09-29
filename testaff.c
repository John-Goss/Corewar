/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testaff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:07:07 by lbaudran          #+#    #+#             */
/*   Updated: 2016/09/29 14:09:20 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			delete_win(WINDOW *test_window)
{
	box(test_window, 0, 0);
	move(0, 0);
	delwin(test_window);
	refresh();
}

static WINDOW		*create_win(WINDOW *win)
{
	WINDOW	*tmp;

	tmp = NULL;
	if (win)
		delwin(win);
	tmp = initscr();
	newwin(0, 0, 0, 0);
	box(tmp, ACS_VLINE, ACS_HLINE);
	get_win_addr(tmp);
	refresh();
	return (tmp);
}

static void			print_str(char *mem)
{
	int	ptr;
	int	n;
	int	j;

	ptr = 0;
	j = 1;
	while (ptr <= (MEM_SIZE - COLS - 2))
	{
		n = COLS - 2;
		mvaddnstr(LINES - LINES + j, COLS - COLS + 1, mem + ptr, n);
		ptr += n;
		j++;
	}
	refresh();
}

/*static WINDOW		*rest_wsize(WINDOW *window, char *mem)
{
	WINDOW	*tmp;

	tmp = NULL;
	clear();
	if (window)
		delete_win(window);
	tmp = create_win();
	print_str(mem);
	return (tmp);
}
*/
static void			signal_catch(int sig_num)
{
	WINDOW	*tmp;
	char	*mem;

	(void)sig_num;
	tmp = NULL;
	mem = get_str_addr(NULL);
	tmp = get_win_addr(NULL);
	tmp = create_win(tmp);
	print_str(mem);
}

static int			getch_aff(WINDOW *window, char *mem)
{
	int			i;

	signal(SIGWINCH, &signal_catch);
	while (42)
	{
		i = getch();
/*		if (i == 28)
		{
			refresh();
			if (window)
				delete_win(window);
			while (COLS <= 50 || LINES <= 50)
			{
				clear();
				mvprintw(LINES / 2, COLS / 2, "UP SIZE");
				refresh();
				if (LINES > 50 && COLS > 50)
				{
					move(1, 1);
					if (window)
						delete_win(window);
					break ;
				}
			}
			window = create_win();
			window = rest_wsize(window, get_str_addr(mem));
			continue ;
		}
		else */if (i == 27)
		{
			clear();
			delete_win(window);
			endwin();
			exit(0);
		}
		else if ((i == KEY_DOWN) || (i == KEY_UP) || (i == KEY_RIGHT)
			|| (i == KEY_LEFT))
		{
			print_str(get_str_addr(mem));
			continue ;
		}
	}
}

int					aff_window(char *mem)
{
	WINDOW	*window;
	int		i;

	window = NULL;
	window = create_win(NULL);
	noecho();
	raw();
	refresh();
	keypad(window, TRUE);
	return (i = getch_aff(window, mem));
}
