/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:21:15 by tbui              #+#    #+#             */
/*   Updated: 2016/10/21 16:04:57 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		apply_live(t_data *data, t_list *elem)
{
	t_desc	*desc;
	int		nb_champ;
	int		i;

	nb_champ = (data->map[(elem->pc + 1) % MEM_SIZE] << 24 & 0xff000000) |
	(data->map[(elem->pc + 2) % MEM_SIZE] << 16 & 0xff0000) |
	(data->map[(elem->pc + 3) % MEM_SIZE] << 8 & 0xff00) |
	(data->map[(elem->pc + 4) % MEM_SIZE] & 0xff);

	elem->pc = ((elem->pc + 5) % MEM_SIZE) % IDX_MOD;
	data->live_cpt++;
	while (desc)
	{
		if (nb_champ == desc->nb_champ)
			data->last_live_nb_champ = nb_champ;
		desc = desc->next;
	}
}

//takes two paramters of which the third will always be register
void		apply_zjmp(t_data *data, t_list *elem, int *params)
{
    if (elem->carry == 1)
            elem->pc = (elem->pc + (params[0] % MEM_SIZE) % IDX_MOD);
}
