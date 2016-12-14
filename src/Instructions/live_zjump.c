/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:16 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/14 16:29:19 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** takes two paramters of which the third will always be register.
*/

void		apply_live(t_data *data, t_list *elem)
{
	int		nb_champ;
	t_desc	*desc;

	desc = data->desc;
	nb_champ = (data->map[(elem->pc + 1) % MEM_SIZE] << 24 & 0xff000000) |
		(data->map[(elem->pc + 2) % MEM_SIZE] << 16 & 0xff0000) |
		(data->map[(elem->pc + 3) % MEM_SIZE] << 8 & 0xff00) |
		(data->map[(elem->pc + 4) % MEM_SIZE] & 0xff);
	elem->pc = ((elem->pc + 5) % MEM_SIZE);
	(elem->live)++;
	(data->live_cpt)++;
	while (desc)
	{
		(desc->live)++;
		if (desc->nb_champ && nb_champ && nb_champ == desc->nb_champ &&
				!desc->dead)
		{
			data->last_live_nb_champ = nb_champ;
			if (data->flag_visu == 0)
				ft_printf("Un processus dit que le joueur %d (%s) est en vie\n",
						nb_champ, desc->name);
		}
		desc = desc->next;
	}
}

void		apply_zjmp(t_data *data, t_list *elem, unsigned int *params)
{
	short	i;

	(void)data;
	i = ((short)params[0]) % IDX_MOD;
	if (i < 0)
	{
		i %= MEM_SIZE;
		i = MEM_SIZE + i;
	}
	if (elem->carry == 1)
		elem->pc = (elem->pc + i) % MEM_SIZE;
}
