/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:21:15 by tbui              #+#    #+#             */
/*   Updated: 2016/11/03 17:20:48 by lbaudran         ###   ########.fr       */
/*   Updated: 2016/11/02 16:16:24 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		apply_live(t_data *data, t_list *elem)
{
	t_desc	*desc;
	int		nb_champ;

	desc = data->desc;
	nb_champ = (data->map[(elem->pc + 1) % MEM_SIZE] << 24 & 0xff000000) |
	(data->map[(elem->pc + 2) % MEM_SIZE] << 16 & 0xff0000) |
	(data->map[(elem->pc + 3) % MEM_SIZE] << 8 & 0xff00) |
	(data->map[(elem->pc + 4) % MEM_SIZE] & 0xff);

	elem->pc = ((elem->pc + 5) % MEM_SIZE) % IDX_MOD;
	data->live_cpt++;
	elem->live++;
	while (desc)
	{
		if (desc->nb_champ && nb_champ && nb_champ == desc->nb_champ)
		{
			data->last_live_nb_champ = nb_champ;
			if (data->flag_visu == 0)
				ft_printf("Un processus dit que le joueur %d(%s) est en vie\n",
					nb_champ, desc->name);
		}
		desc = desc->next;
	}
}

//takes two paramters of which the third will always be register
void		apply_zjmp(t_data *data, t_list *elem, unsigned int *params)
{
    if (elem->carry == 1)
            elem->pc = (elem->pc + (params[0] % MEM_SIZE) % IDX_MOD);
}
