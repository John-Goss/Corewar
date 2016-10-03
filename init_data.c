/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 16:27:09 by jle-quer          #+#    #+#             */
/*   Updated: 2016/10/03 15:26:33 by jle-quer         ###   ########.fr       */
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
	if (!*begin)
	{
		if (!(*begin = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		ft_bzero((*begin)->reg_number, REG_NUMBER);
		(*begin)->prev = NULL;
		(*begin)->next = NULL;
		(*begin)->pc = 0;
		(*begin)->reg_number[0] = champ_nb;
		(*begin)->carry = 0;
		(*begin)->process_nb = 0;
		(*begin)->action_time = 0;
		return (*begin);
	}
	if (!((*begin)->prev = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	ft_bzero((*begin)->reg_number, REG_NUMBER);
	(*begin)->prev->next = (*begin);
	(*begin)->prev->prev = NULL;
	(*begin)->prev->pc = pc;
	(*begin)->prev->reg_number[0] = champ_nb;
	(*begin)->prev->carry = 0;
	(*begin)->prev->process_nb++;
	(*begin)->prev->action_time = 0;
	*begin = (*begin)->prev;
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

void		init_struct(t_data *data)
{
	int		i;

	i = 0;
	ft_bzero(data->map, MEM_SIZE);
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
