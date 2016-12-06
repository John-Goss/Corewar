/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:40:36 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/06 15:37:31 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		set_live_infos(t_data *data)
{
	mvprintw(35, 195, "----------------------------");
	mvprintw(40, 196, "Cycle To Die : %d", data->cycle_to_die);
	mvprintw(43, 196, "Cycle : %d", data->cycle);
	mvprintw(46, 196, "Exe Process : %d", data->begin->process_nb + 1);
	mvprintw(52, 196, "Total Live : %d", data->live_cpt);
	mvprintw(55, 196, "Last Champ ID Live : %d", data->last_live_nb_champ);
	if (data->flag_slowmode == 1)
	{
		mvprintw(77, 197, "|| Slowmode Activated ||");
		mvprintw(78, 196, "Press Space for next cycle");
	}
	return (0);
}

void	init_infos_box(t_data *data)
{
	t_desc	*tmp;
	int		pos_y;
	int		pos_x;

	pos_y = 20;
	pos_x = 195;
	tmp = data->desc;
	werase(data->display->info);
	box(data->display->info, ACS_VLINE, ACS_HLINE);
	wrefresh(data->display->info);
	attron(A_UNDERLINE);
	mvprintw(16, 196 + 13 / 2, "Infos Players");
	attroff(A_UNDERLINE);
	while (tmp)
	{
		mvprintw(pos_y, 195, "Player %d - (%s)",
				tmp->nb_champ, tmp->name);
		pos_y += 3;
		tmp = tmp->next;
	}
	set_live_infos(data);
	refresh();
}

void	display_clear_pc(t_data *data, int i, int *x_y, int champ_id)
{
	if (champ_id < 0 && champ_id != -1)
		champ_id = -(champ_id);
	champ_id %= 255;
	attron(COLOR_PAIR(champ_id));
	mvwprintw(data->display->screen, x_y[1], x_y[0], "%.2hhx",
			data->display->mem[i]);
	if (champ_id != -1)
		attroff(COLOR_PAIR(champ_id));
}

void	display_pc(t_data *data, int i, int *x_y, int champ_id)
{
	if (champ_id < 0)
		champ_id = -(champ_id);
	champ_id %= 255;
	attron(A_STANDOUT | COLOR_PAIR(champ_id));
	mvwprintw(data->display->screen, x_y[1], x_y[0], "%.2hhx",
			data->display->mem[i]);
	attroff(A_STANDOUT | COLOR_PAIR(champ_id));
}

void	display_classique(t_data *data, int i, int *x_y, int champ_id)
{
	if (champ_id < 0 && champ_id != -1)
		champ_id = -champ_id;
	champ_id %= 255;
	if (champ_id != -1)
		attron(COLOR_PAIR(champ_id));
	mvwprintw(data->display->screen, x_y[1], x_y[0], "%.2hhx",
			data->display->mem[i]);
	if (champ_id != -1)
		attroff(COLOR_PAIR(champ_id));
}
