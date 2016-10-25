/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testaff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 15:07:07 by lbaudran          #+#    #+#             */
/*   Updated: 2016/10/25 13:28:44 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <sys/ioctl.h>
#include <signal.h>

void				delete_win(t_display *display)
{
	if (display->info)
		delwin(display->info);
	if (display->win)
		delwin(display->win);
	if (display->header)
		delwin(display->header);
	if (display->screen)
		delwin(display->screen);
	clear();
	refresh();
	endwin();
}

static void			sigkill(int code)
{
	WINDOW		*tmp;
	t_display	*ptr;

	code = 0;
	tmp = NULL;
	ptr = NULL;
	ptr = get_dsp_struct_addr(NULL);
	tmp = get_win_addr(NULL);
	if (ptr)
		exit(0);
	//delete_win(ptr);
	//clear();
	//free(tmp);
	//exit(0);
}

static void			create_win(t_display *display)
{
	display->screen = initscr();
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
	
	t_display	*tmp;
	tmp = NULL;
	tmp = get_dsp_struct_addr(NULL);

	mvwprintw(display->screen, 1, 1, "%p", &tmp);
	mvwprintw(display->screen, 2, 1, "%p", &data->display);
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
	refresh();
}

static int			getch_aff(t_data *data)
{
	int			keycode;

	mvwprintw(data->display->screen, 44, 194/2 - 58/2,
			"Press Space_Key for run the game or S for run the slowmode.");
	signal(SIGINT, &sigkill); // Catch ctrl-c signal
	while (42)
	{
		keycode = getch();
		if (keycode == 27) // ESC Key
			sigkill(1);
		else if (keycode == 's')
		{
			data->flag_slowmode = 1;
			werase(data->display->win);
			print_str(data->display, data);
			break ;
		}
		else if (keycode == 32) // Space Key
		{
			werase(data->display->win);
			print_str(data->display, data);
			break ;
		}
	}
	return (0);
}

int					aff_window(t_data *data)
{
	t_display		display;
	struct winsize	t;

	display = (t_display){NULL, NULL, NULL, NULL, NULL};
	if ((ioctl(0, TIOCGWINSZ, &t) < 0))
		return (-1);
	if (t.ws_col < 224 || t.ws_row < 81)
	{
		ft_printf("\nTOO SHORT SIZE FOR DISPLAY\nLINES MIN: 81 / Value TTY: ");
		ft_printf("%d\nCOLS MIN: 224 / Value TTY: %d\n",t.ws_row, t.ws_col);
		exit(1);
	}
	create_win(&display);
	noecho();
	refresh();
	keypad(display.screen, TRUE);
	data->display = &display;
	init_infos_box(data);
	get_dsp_struct_addr(data->display);
	getch_aff(data);
	return (1);
}
