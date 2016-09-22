/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testaff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:07:07 by lbaudran          #+#    #+#             */
/*   Updated: 2016/09/22 12:52:47 by jle-quer         ###   ########.fr       */
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
static WINDOW		*create_win(int lines, int cols)
{
	WINDOW	*test_window;
	int		height;
	int		width;

	height = cols - (cols / 90);
	width = lines - (lines / 90);
	test_window = newwin(height, width, 0, 0);
	box(test_window, '|', '-');
	wrefresh(test_window);
	width = 0;
//	while (width != 16)
//		create_subwin(lines, cols, width++);
	refresh();
	return (test_window);
}

static void			delete_win(WINDOW *test_window)
{
	wborder(test_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(test_window);
	refresh();
}

static int			getch_aff(WINDOW *test, int lines, int col)
{
	int	i;

	while (1)
	{
		i = getch();
		if (i == 410)
		{
			refresh();
			if (test)
				delete_win(test);
			getmaxyx(stdscr, col, lines);
			if (col <= 15)
				printw("Taille trop petite");
			else
				test = create_win(lines, col);
		}
		if ((i == KEY_DOWN) || (i == KEY_UP) || (i == KEY_RIGHT)
				|| (i == KEY_LEFT) || (i == 27))
		{
			clear();
			refresh();
			return (i);
		}
	}
}

int					aff_window()
{
	WINDOW	*test_window;
	int		lines;
	int		cols;
	int		i;

	initscr();
	noecho();
	raw();
	refresh();
	keypad(stdscr, TRUE);
	test_window = NULL;
	getmaxyx(stdscr, cols, lines);
	if (cols <= 15)
		printw("Taille trop petite");
	else
		test_window = create_win(lines, cols);
	return (i = getch_aff(test_window, lines, cols));
}
