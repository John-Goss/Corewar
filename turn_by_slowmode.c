/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_by_slowmode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 17:49:58 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/03 13:15:32 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	turn_by_slowmode(t_data *data)
{
	int	keycode;

	keycode = 0;
	while (42)
	{
		keycode = getch();
		if (keycode == 32)
		{
			werase(data->display->win);
			print_str(data);
			turn(data);
			(data->cycle)++;
			if ((--(data->cycle_to_die)) <= 0)
				if (verif_end(data) == 1)
					break ;
			init_infos_box(data);
		}
	}
	return (0);
}

int	turn_by_none(t_data *data)
{
	while (42)
	{
		if (data->flag_visu == 1)
		{
			werase(data->display->win);
			print_str(data);
		}
		turn(data);
		(data->cycle)++;
		if ((--(data->cycle_to_die)) <= 0)
			if (verif_end(data) == 1)
				break ;
		if (data->flag_visu == 1)
			init_infos_box(data);
	}
	return (0);
}
