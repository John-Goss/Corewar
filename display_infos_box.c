/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_infos_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:40:36 by jle-quer          #+#    #+#             */
/*   Updated: 2016/10/20 14:57:15 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	init_infos_box(t_data *data)
{
	t_desc	*tmp;
	int		pos_y;

	tmp = data->desc;
	pos_y = 19;
	mvwprintw(data->display->screen, 16, 196 + 13/2, "Infos Players");
	while (tmp)
	{
		mvwprintw(data->display->screen, pos_y, 196, "Player %d - %s", tmp->nb_champ, tmp->name);
		tmp = tmp->next;
		pos_y += 3;
	}
	refresh();
	return (0);
}
