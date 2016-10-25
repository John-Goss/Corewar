/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:40:36 by jle-quer          #+#    #+#             */
/*   Updated: 2016/10/25 18:05:04 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		set_live_infos(t_data *data)
{
	mvwprintw(data->display->screen, 35, 195, "----------------------------");
	mvwprintw(data->display->screen, 40, 196, "Cycle To Die : %d", data->cycle_to_die);
	mvwprintw(data->display->screen, 43, 196, "Cycle : %d", data->cycle);
	mvwprintw(data->display->screen, 46, 196, "Exe Process : %d", data->begin->process_nb);
	mvwprintw(data->display->screen, 52, 196, "Total Live : %d", data->live_cpt);
	mvwprintw(data->display->screen, 55, 196, "Last Champ ID Live : %d", data->last_live_nb_champ);
	if (data->flag_slowmode == 1)
	{
		mvwprintw(data->display->screen, 77, 197, "|| Slowmode Activated ||");
		mvwprintw(data->display->screen, 78, 196, "Press Space for next cycle");
	}
	refresh();
	return (0);
}

int		init_infos_box(t_data *data)
{
	t_desc	*tmp;
	int		pos_y;
	int		pos_x;

	tmp = data->desc;
	pos_y = 20;
	pos_x = 195;
	werase(data->display->info);
	attron(A_UNDERLINE);
	mvwprintw(data->display->screen, 16, 196 + 13/2, "Infos Players");
	attroff(A_UNDERLINE);
	while (tmp)
	{
		mvwprintw(data->display->screen, pos_y, 195, "Player %d - (%s)",
				tmp->nb_champ, tmp->name);
		pos_y += 3;
		tmp = tmp->next;
	}
	refresh();
	set_live_infos(data);
	return (0);
}
