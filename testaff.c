/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testaff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:07:07 by lbaudran          #+#    #+#             */
/*   Updated: 2016/10/03 18:57:59 by jle-quer         ###   ########.fr       */
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

static void			create_win(t_display display)
{
	display.screen = initscr();
	display.win = subwin(display.screen, 66, 130, 0, 0);
	box(display.win, ACS_VLINE, ACS_HLINE);
	display.mem = get_str_addr(NULL);
}

static void			print_str(char *mem)
{
	int	ptr;
	int	n;
	int	j;

	ptr = 0;
	j = 1;
	while (ptr < MEM_SIZE * 2)
	{
		n = 130 - 2;
		mvprintw(j, 1, "%.*hhx", 130 - 2, mem + ptr);
		ptr += n;
		j++;
	}
	refresh();
}

/*
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
*/

static int			getch_aff(t_display display)
{
	int			i;

	print_str(display.mem);
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
			delete_win(display.win);
			endwin();
			exit(0);
		}
		else if ((i == KEY_DOWN) || (i == KEY_UP) || (i == KEY_RIGHT)
			|| (i == KEY_LEFT))
		{
			print_str(display.mem);
			continue ;
		}
	}
}

int					aff_window()
{
	t_display	display;
	int			i;

	display = (t_display){NULL, NULL, NULL};
	create_win(display);
	noecho();
	raw();
	refresh();
	keypad(display.win, TRUE);
	return (i = getch_aff(display));
}
