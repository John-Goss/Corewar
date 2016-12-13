/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:52:26 by lbaudran          #+#    #+#             */
/*   Updated: 2016/12/13 19:30:21 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		end(t_data *data)
{
	t_desc	*elem;

	elem = data->desc;
	if (data->flag_visu == 1)
		delete_win(data->display);
	if (data->last_live_nb_champ)
	{
		while (elem && elem->nb_champ != data->last_live_nb_champ)
			elem = elem->next;
		ft_printf("Le joueur %d (%s) a gagne\n", elem->nb_champ, elem->name);
	}
	else
		exit(write(1, "Aucun live n'a ete fait\n", 24));
}

int			verif_end(t_data *data)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (data->check == (MAX_CHECKS - 1) || (int)data->live_cpt >= NBR_LIVE)
	{
		data->cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * data->ctd_nbr);
		data->check = 0;
		data->ctd_nbr++;
	}
	else
	{
		data->cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * (data->ctd_nbr - 1));
		(data->check)++;
	}
	check_who_is_alive(data);
	check_who_is_alive_champ(data);
	data->live_cpt = 0;
	if (data->begin && data->cycle_to_die > 0)
		return (0);
	return (1);
}

t_list		*destroy_elem(t_data *data, t_list *elem)
{
	t_list *tmp;

	tmp = elem->next;
	if (elem->next == NULL)
	{
		if (elem->prev)
			elem->prev->next = NULL;
		else
			(data->begin = NULL);
		free(elem);
		return (NULL);
	}
	if (elem->prev)
	{
		tmp->prev = elem->prev;
		tmp->prev->next = tmp;
		free(elem);
		return (tmp);
	}
	data->begin = elem->next;
	data->begin->prev = NULL;
	free(elem);
	return (data->begin);
}

void		check_who_is_alive_champ(t_data *data)
{
	t_desc	*elem;

	elem = data->desc;
	while (elem)
	{
		if (elem->dead == 0 && elem->live > 0)
			elem->live = 0;
		else
			elem->dead = 1;
		elem = elem->next;
	}
}

void		check_who_is_alive(t_data *data)
{
	t_list	*elem;

	elem = data->begin;
	while (elem)
	{
		if (elem->live == 0)
		{
			if (data->flag_visu == 1)
				clear_died_pc(data, elem);
			elem = destroy_elem(data, elem);
		}
		else
		{
			elem->live = 0;
			elem = elem->next;
		}
	}
	return ;
}
