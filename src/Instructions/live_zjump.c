/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_zjump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:16 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/28 18:56:44 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void	print_process_name(t_data *data, int nb_champ)
{
	t_desc	*tmp;

	tmp = data->desc;
	while (tmp)
	{
		if (tmp->nb_champ == nb_champ)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
		ft_printf("Un processus dit que le joueur %d (%s) est en vie\n",
				nb_champ, tmp->name);
}

void		apply_live(t_data *data, t_list *elem)
{
	int		nb_champ;

	nb_champ = (data->map[(elem->pc + 1) % MEM_SIZE] << 24 & 0xff000000) |
		(data->map[(elem->pc + 2) % MEM_SIZE] << 16 & 0xff0000) |
		(data->map[(elem->pc + 3) % MEM_SIZE] << 8 & 0xff00) |
		(data->map[(elem->pc + 4) % MEM_SIZE] & 0xff);
	elem->pc = ((elem->pc + 5) % MEM_SIZE);
	if (nb_champ == elem->nb_champ)
	{
		data->live_cpt++;
		elem->live++;
		data->last_live_nb_champ = nb_champ;
		if (data->flag_visu == 0)
			print_process_name(data, nb_champ);
	}
}

/*
** takes two paramters of which the third will always be register.
*/

void		apply_zjmp(t_data *data, t_list *elem, unsigned int *params)
{
	(void)data;
	if (elem->carry == 1)
		elem->pc = (((elem->pc - (elem->pc % IDX_MOD)) +
					(elem->pc + params[0])) % IDX_MOD) % MEM_SIZE;
}
