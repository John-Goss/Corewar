/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testaff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:07:07 by lbaudran          #+#    #+#             */
/*   Updated: 2016/09/28 17:40:09 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
static WINDOW		*create_subwin(int lines, int cols, int y)
{
	WINDOW	*sub_window;
	int		starthauteur;
	int		startlongueur;
	int		i;

	starthauteur = ((cols - (4 * (cols / 8))) / 5);
	startlongueur = ((lines - (4 * (lines / 8))) / 5);
	i = y / 4;
	y = y % 4;
	starthauteur = (starthauteur * (i + 1) + (cols / 8) * (i));
	startlongueur = (startlongueur * (y + 1) + (lines / 8) * (y));
	mvprintw(starthauteur + 1, startlongueur + 1, "%d", tab[i][y]);
	sub_window = newwin((cols / 8), (lines / 8), starthauteur, startlongueur);
	box(sub_window, '|', '-');
	wrefresh(sub_window);
	refresh();
	return (sub_window);
}
*/
static WINDOW		*create_win()
{
	WINDOW	*tmp;

	tmp = NULL;
	tmp = initscr();
	newwin(0, 0, 0, 0);
	box(tmp, ACS_VLINE, ACS_HLINE);
	refresh();
	return (tmp);
}

static void			delete_win(WINDOW *test_window)
{
	delwin(test_window);
	box(test_window, ACS_VLINE, ACS_HLINE);
	move(0, 0);
	refresh();
}

static int			getch_aff(WINDOW *window, char *mem)
{
	int			i;
	int			n;
	int			j;
	int			ptr;

	ptr = 0;
	j = 1;
	while (42)
	{
		i = getch();
		if (i == 28)
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
			continue ;
		}
		else if (i == 27)
		{
			clear();
			delete_win(window);
			endwin();
			exit(0);
		}
		else if ((i == KEY_DOWN) || (i == KEY_UP) || (i == KEY_RIGHT)
				|| (i == KEY_LEFT))
		{
			while (ptr <= (MEM_SIZE - COLS - 2))
			{
				n = COLS - 2;
				mvaddnstr(LINES - LINES + j, COLS - COLS + 1, mem + ptr, n);
				ptr += n;
				j++;
			}
			refresh();
			continue ;
		}
	}
}

int					aff_window(char *mem)
{
	WINDOW	*window;
	int		i;

	window = NULL;
	window = create_win();
	noecho();
	raw();
	refresh();
	keypad(window, TRUE);
/*	while (COLS <= 50 || LINES <= 50)
	{
		clear();
		mvprintw(LINES / 2, COLS / 2, "UP SIZE");
		refresh();
		getmaxyx(stdscr, LINES, COLS);
		getch();
		if (LINES > 50 && COLS > 50)
			break ;
	}
*/	return (i = getch_aff(window, mem));
}
