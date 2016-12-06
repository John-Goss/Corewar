/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testaff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 14:54:39 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/06 15:41:42 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <sys/ioctl.h>
#include <signal.h>

static void		init_pair_by_id(t_data *data)
{
	int		cpt;
	int		i;
	t_desc	*tmp;

	cpt = 0;
	tmp = data->desc;
	while (cpt < data->nb_champ)
	{
		i = tmp->nb_champ;
		if (i < 0)
			i = -i;
		if (cpt == 0)
			init_pair(i % 255, COLOR_RED, COLOR_BLACK);
		else if (cpt == 1)
			init_pair(i % 255, COLOR_BLUE, COLOR_BLACK);
		else if (cpt == 2)
			init_pair(i % 255, COLOR_GREEN, COLOR_BLACK);
		else if (cpt == 3)
			init_pair(i % 255, COLOR_YELLOW, COLOR_BLACK);
		tmp = tmp->next;
		cpt++;
	}
}

static void		create_win(t_data *data, t_display *display)
{
	display->screen = initscr();
	display->header = subwin(display->screen, 15, 224, 0, 0);
	display->win = subwin(display->screen, 66, 194, 15, 0);
	display->info = subwin(display->screen, 66, 30, 15, 194);
	box(display->win, ACS_VLINE, ACS_HLINE);
	box(display->info, ACS_VLINE, ACS_HLINE);
	box(display->header, ACS_VLINE, ACS_HLINE);
	start_color();
	init_pair_by_id(data);
	attron(A_UNDERLINE | A_BOLD);
	mvwprintw(display->screen, 15 / 2 - 1, 224 / 2 - 22 / 2,
			"COREWAR CHAMPIONSHIP'S");
	attroff(A_UNDERLINE | A_BOLD);
	mvwprintw(display->screen, 15 / 2 - 1, 224 / 2 - 22 / 2,\
			"COREWAR CHAMPIONSHIP'S");
	attroff(A_UNDERLINE | A_BOLD);
	mvwprintw(display->screen, 15 / 2 + 1, 224 / 2 - 16 / 2, \
			"|| BattleZONE ||");
	display->mem = get_str_addr(NULL);
	get_win_addr(display->screen);
}

void			print_str(t_data *data)
{
	int	i;
	int	x_y[2];
	int	*pc;
	int	nb_champ;

	pc = NULL;
	i = 0;
	x_y[0] = 1;
	x_y[1] = 16;
	pc = set_array_pc(data->begin);
	while (x_y[1] < 80)
	{
		while (x_y[0] < 192)
		{
			nb_champ = find_pc_pos(data->begin, pc, data->nb_champ, i);
			nb_champ != -1 ? display_pc(data, i, x_y, nb_champ) \
			: display_classique(data, i, x_y, champ_id(data, i));
			x_y[0] += 3;
			i++;
		}
		x_y[1]++;
		x_y[0] = 1;
	}
	init_infos_box(data);
	refresh();
}

static int		getch_aff(t_data *data)
{
	int	keycode;

	mvwprintw(data->display->screen, 44, (194 / 2) - (58 / 2),
			"Press Space_Key for run the game or S for run the slowmode.");
	signal(SIGINT, &sigkill);
	while (42)
	{
		(keycode = getch()) == 27 ? sigkill(1) : 0;
		if (keycode == 's')
		{
			data->flag_slowmode = 1;
			werase(data->display->win);
			print_str(data);
			break ;
		}
		else if (keycode == 32)
		{
			werase(data->display->win);
			print_str(data);
			break ;
		}
	}
	return (0);
}

int				aff_window(t_data *data)
{
	t_display		*display;
	struct winsize	t;

	if (!(display = (t_display*)malloc(sizeof(t_display))))
		return (0);
	*display = (t_display){NULL, NULL, NULL, NULL, NULL};
	if ((ioctl(0, TIOCGWINSZ, &t) < 0))
		return (-1);
	if (t.ws_col < 224 || t.ws_row < 81)
	{
		ft_printf("\nTOO SHORT SIZE FOR DISPLAY\nLINES MIN: 81 / Value TTY: ");
		ft_printf("%d\nCOLS MIN: 224 / Value TTY: %d\n", t.ws_row, t.ws_col);
		exit(1);
	}
	create_win(data, display);
	noecho();
	keypad(display->screen, TRUE);
	data->display = display;
	get_dsp_struct_addr(data->display);
	getch_aff(data);
	return (1);
}
