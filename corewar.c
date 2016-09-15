/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 12:56:03 by lbaudran          #+#    #+#             */
/*   Updated: 2016/09/15 17:00:46 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 1;
	init_struct(&data);
	check_flag(argc, argv, &data);
//	parse_map(argc, argv, &data);
	verif_valid(argc, argv, &data);
//	if (data.flag_visu)
//		init_vis(&data);
	while (42)
	{
		turn(&data);
		(data.cycle)++;
		if ((--(data.cycle_to_die)) == 0)
			if (verif_end(&data) == 1)
				break;
	}
//	end(data);
}

void		parse_map(int argc, char **argv, t_data *data)
{
	
}

void		turn(t_data *data)
{
	t_list *elem;

	elem = data->begin;
	while (elem)
	{
//		process_action(data, elem);
		elem = elem->next;
	}
			return ;
}

t_list		*destroy_elem(t_list *elem)
{
	t_list *tmp;

	tmp = elem->next;
	tmp->prev = elem->prev;
	tmp->prev->next = tmp;
	free(elem);
	return (tmp);
}

void		check_who_is_alive(t_data *data)
{
	int		i;
	t_list	*elem;

	elem = data->begin;
	i = 1;
	while (i < data->nb_champ)
	{
		if (data->tab_live[i] < NBR_LIVE)
			data->statut_champ[i] = 1;
		i++;
	}
	while (elem)
	{
		if (elem->live == 0)
			elem = destroy_elem(elem);
		else
			elem = elem->next;
	}
	return ;
}

int			verif_end(t_data *data)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	data->cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * data->cycle_to_die_nbr);
	data->cycle_to_die_nbr++;
	check_who_is_alive(data);
	while (i < data->nb_champ)
	{
		if (data->statut_champ[i++] == 0)
			j++;
		if (j >= 2)
			return (0);
	}
	return (1);
}

t_desc		*create_desc(t_desc *desc)
{
	t_desc	*elem;

	if (!desc)
	{
		desc = (t_desc *)malloc(sizeof(t_desc));
		desc->next = NULL;
		desc->name = NULL;
		desc->size = 0;
		desc->desc = NULL;
		return (desc);
	}
	while (elem)
		elem = elem->next;
	elem = (t_desc *)malloc(sizeof(t_desc));
	elem->next = NULL;
	elem->name = NULL;
	elem->size = 0;
	elem->desc = NULL;
	return (elem);
}

t_list		*create_elem(t_list *begin, int champ_nb, int pc)
{
	t_list	*elem;

	if (!begin)
	{
		begin = (t_list *)malloc(sizeof(t_list));
		begin->prev = NULL;
		begin->next = NULL;
		begin->pc = 0;
		begin->champ_nb = 0;
		begin->carry = 0;
		begin->process_nb = 0;
		begin->action_time = 0;
		return (begin);
	}
	elem = begin;
	elem->prev = (t_list *)malloc(sizeof(t_list));
	elem->prev->next = elem;
	elem->prev->prev = NULL;
	elem->prev->pc = pc; // besoin du pc
	elem->prev->champ_nb = pc; // besoin du champ_nb
	elem->prev->carry = 0;
	elem->prev->process_nb = elem->process_nb + 1;
	elem->prev->action_time = 0;
	begin = elem->prev;
	return (begin);
}

int			check_flag(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (i <= argc)
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
	data->flag_visu = 0;
	data->cycle = 0;
	data->cycle_to_die = CYCLE_TO_DIE;
	data->cycle_to_die_nbr = 1;
	data->begin = NULL;
	data->begin = create_elem(data->begin, 0, 0);
	data->size_champ = 0;
	data->nb_champ = 0;
	while (i <= MAX_PLAYERS + 1)
	{
		data->statut_champ[i] = 0;
		data->tab_live[i++] = 0;
	}
}

int			verif_valid(int argc, char **argv, t_data *data)
{
	if (data->nb_champ > MAX_PLAYERS + 1)
		exit(write(1, "Nombre de champions incorrect\n", 30));
	if (data->size_champ)
		exit(write(1, "Taille champion incorrecte\n", 27));
	return (0);
}
