/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 16:27:09 by jle-quer          #+#    #+#             */
/*   Updated: 2016/09/27 15:38:09 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_desc		*create_desc(t_desc **desc)
{
	t_desc	*elem;

	elem = *desc;
	if (!*desc)
	{
		if (!(*desc = (t_desc *)malloc(sizeof(t_desc))))
			return (NULL);
		(*desc)->next = NULL;
		(*desc)->name = (char *)malloc(129 *sizeof(char));
		(*desc)->size = 0;
		(*desc)->desc = (char *)malloc(2049 *sizeof(char));
		return (*desc);
	}
	while (elem)
		elem = elem->next;
	if (!(elem = (t_desc *)malloc(sizeof(t_desc))))
		return (NULL);
	elem->next = NULL;
	elem->name = (char *)malloc(129 * sizeof(char));
	elem->size = 0;
	elem->desc = (char *)malloc(2049 * sizeof(char));
	return (elem);
}

t_list		*create_elem(t_list **begin, int champ_nb, int pc)
{
	t_list	*elem;

	if (!*begin)
	{
		if (!(*begin = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		(*begin)->prev = NULL;
		(*begin)->next = NULL;
		(*begin)->pc = 0;
		(*begin)->champ_nb = champ_nb;
		(*begin)->carry = 0;
		(*begin)->process_nb = 0;
		(*begin)->action_time = 0;
		return (*begin);
	}
	elem = *begin;
	if (!(elem->prev = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	elem->prev->next = elem;
	elem->prev->prev = NULL;
	elem->prev->pc = pc; // besoin du pc
	elem->prev->champ_nb = pc; // besoin du champ_nb
	elem->prev->carry = 0;
	elem->prev->process_nb = elem->process_nb + 1;
	elem->prev->action_time = 0;
	*begin = elem->prev;
	return (*begin);
}

int			check_flag(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!strcmp(argv[1], "-n"))
			data->flag_visu = 1;
		i++;
	}
	return (0);
}

void		put_zero(char *str, int n)
{
	int		i;

	i = 0;
	while(i < n)
		str[i++] = '0';
}

void		init_struct(t_data *data)
{
	int		i;

	i = 0;
	put_zero(data->map, MEM_SIZE);
	data->flag_slowmode = 0;
	data->flag_visu = 0;
	data->cycle = 0;
	data->cycle_to_die = CYCLE_TO_DIE;
	data->cycle_to_die_nbr = 1;
	data->begin = NULL;
	data->begin = create_elem(&data->begin, 0, 0);
	data->desc = NULL;
	data->nb_champ = 0;
	data->live_cpt = 0;
	while (i <= MAX_PLAYERS + 1)
	{
		data->statut_champ[i] = 0;
		data->tab_live[i++] = 0;
	}
}
