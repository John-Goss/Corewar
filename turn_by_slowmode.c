/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_by_slowmode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 17:49:58 by jle-quer          #+#    #+#             */
/*   Updated: 2016/10/25 18:06:52 by jle-quer         ###   ########.fr       */
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
//			set_live_infos(data);
			init_infos_box(data);
			turn(data);
			(data->cycle)++;
			if ((--(data->cycle_to_die)) <= 0)
				if (verif_end(data) == 1)
					break ;
		}
	}
	return (0);
}
