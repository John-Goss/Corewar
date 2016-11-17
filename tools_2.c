/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:45:29 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/17 18:15:27 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		champ_id(t_data *data, int index)
{
	t_desc	*tmp;

	set_desc_pc(data);
	tmp = data->desc;
	while (tmp)
	{
		if (index >= tmp->pc && index < tmp->pc + tmp->size)
			return (tmp->nb_champ);
		tmp = tmp->next;
	}
	return (-1);
}

int		set_desc_pc(t_data *data)
{
	t_desc	*tmp;
	t_list	*ptr;

	tmp = data->desc;
	while (tmp)
	{
		ptr = data->begin;
		tmp->pc = -1;
		while (tmp->pc == -1)
		{
			if (tmp->nb_champ == ptr->nb_champ)
				tmp->pc = ptr->pc;
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	clear_pc(t_data *data)
{
	int	x_y[2];
	int	*pc;
	int	i;
	int	nb_champ;

	pc = set_array_pc(data->begin);
	i = 0;
	x_y[0] = 1;
	x_y[1] = 16;
	while (x_y[1] < 80)
	{
		while (x_y[0] < 192)
		{
			if ((nb_champ = find_pc_pos(data->begin, pc, data->nb_champ, i)) != -1)
				display_clear_pc(data, i, x_y, nb_champ);
			x_y[0] += 3;
			i++;
		}
		x_y[1]++;
		x_y[0] = 1;
	}
}

void	print_pc(t_data *data)
{
	int	x_y[2];
	int	*pc;
	int	i;
	int	nb_champ;

	pc = set_array_pc(data->begin);
	i = 0;
	x_y[0] = 1;
	x_y[1] = 16;
	while (x_y[1] < 80)
	{
		while (x_y[0] < 192)
		{
			if ((nb_champ = find_pc_pos(data->begin, pc, data->nb_champ, i)) != -1)
				display_pc(data, i, x_y, nb_champ);
			x_y[0] += 3;
			i++;
		}
		x_y[1]++;
		x_y[0] = 1;
	}
	refresh();
}

void	print_index(t_data *data, t_list *elem, int index)
{
	int	x_y[2];
	int	*pc;
	int	i;
	int	nb_champ;

	pc = set_array_pc(data->begin);
	i = 0;
	x_y[0] = 1;
	x_y[1] = 16;
	while (x_y[1] < 80)
	{
		while (x_y[0] < 192)
		{
			if (i == index)
			{
				if ((nb_champ = find_pc_pos(data->begin, pc, data->nb_champ, i))
						!= -1)
					display_pc(data, i, x_y, nb_champ);
				else
					display_classique(data, i, x_y, elem->nb_champ);
			}
			x_y[0] += 3;
			i++;
		}
		x_y[1]++;
		x_y[0] = 1;
	}
	refresh();
}
