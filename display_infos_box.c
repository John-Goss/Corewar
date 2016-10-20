/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:40:36 by jle-quer          #+#    #+#             */
/*   Updated: 2016/10/20 17:20:02 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	init_infos_box(t_data *data)
{
	t_desc	*tmp;
	int		pos_y;
	int		pos_x;

	tmp = data->desc;
	pos_y = 20;
	pos_x = 195;
	attron(A_UNDERLINE);
	mvwprintw(data->display->screen, 16, 196 + 13/2, "Infos Players");
	attroff(A_UNDERLINE);
	while (tmp)
	{
		mvwprintw(data->display->screen, pos_y, 195, "Player %d - (%s)",
				tmp->nb_champ, tmp->name);
		pos_y += 4;
		tmp = tmp->next;
	}
	refresh();
	return (0);
}
