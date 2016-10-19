/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testaff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:07:07 by lbaudran          #+#    #+#             */
/*   Updated: 2016/10/19 19:00:57 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <sys/ioctl.h>
#include <signal.h>

static void			delete_win(WINDOW *test_window)
{
	box(test_window, 0, 0);
	move(0, 0);
	delwin(test_window);
	refresh();
}

static void			sigkill(int code)
{
	WINDOW	*tmp;

	code = 0;
	tmp = NULL;
	tmp = get_win_addr(NULL);
	clear();
	delete_win(tmp);
	endwin();
	free(tmp);
	exit(0);
}

static void			create_win(t_display *display)
{
	display->screen = initscr();
	start_color();
	display->header = subwin(display->screen, 15, 224, 0, 0);
	display->win = subwin(display->screen, 66, 194, 15, 0);
	display->info = subwin(display->screen, 66, 30, 15, 194);
	box(display->win, ACS_VLINE, ACS_HLINE);
	box(display->info, ACS_VLINE, ACS_HLINE);
	box(display->header, ACS_VLINE, ACS_HLINE);
	attron(A_UNDERLINE | A_BOLD);
	mvwprintw(display->screen, 15/2 -1, 224/2 - 22/2, "COREWAR CHAMPIONSHIP'S");
	attroff(A_UNDERLINE | A_BOLD);
	mvwprintw(display->screen, 15/2 + 1, 224/2 - 16/2, "|| BattleZONE ||");
	display->mem = get_str_addr(NULL);
	get_win_addr(display->screen);
}

static void			print_str(t_display *display, t_data *data)
{
	int	i;
	int	x;
	int	y;
	int	*pc;

	pc = NULL;
	i = 0;
	x = 1;
	y = 16;
	pc = set_array_pc(data);
	while (y < 80)
	{
		while (x < 192)
		{
			if (find_pc_pos(data->begin, pc, i))
			{
				attron(A_STANDOUT);
				mvwprintw(display->screen, y, x, "%.2hhx", display->mem[i]);
				attroff(A_STANDOUT);
			}
			else
				mvwprintw(display->screen, y, x, "%.2hhx", display->mem[i]);
			x += 3;
			i++;
		}
		y++;
		x = 1;
	}
	mvwprintw(display->screen, 16, 196, "Valeur de sort PC[0] %d, 1 : %d, 2 : %d", pc[0], pc[1], pc[2]);
	refresh();
}

static int			getch_aff(t_display *display, t_data *data)
{
	int			keycode;

	mvwprintw(display->screen, 44, 194/2 - 33/2,
			"Press Space_Key for run the game.");
	signal(SIGINT, &sigkill); // Catch ctrl-c signal
	while (42)
	{
		keycode = getch();
		if (keycode == 27) // ESC Key
			sigkill(1);
		else if (keycode == 32) // Space Key
		{
			werase(display->win);
			print_str(display, data);
			continue ;
		}
	}
}

int					aff_window(t_data *data)
{
	t_display		display;
	int				i;
	struct winsize	t;

	display = (t_display){NULL, NULL, NULL, NULL, NULL};
	if ((ioctl(0, TIOCGWINSZ, &t) < 0))
		return (-1);
	if (t.ws_col < 224 || t.ws_row < 81)
	{
		ft_printf("\nTOO SHORT SIZE FOR DISPLAY\nLINES MIN: 81 / Value TTY: ");
		ft_printf("%d\nCOLS MIN: 224 / Value TTY: %d\n",t.ws_row, t.ws_col);
		exit(0);
	}
	create_win(&display);
	noecho();
	refresh();
	keypad(display.screen, TRUE);
	return (i = getch_aff(&display, data));
}
