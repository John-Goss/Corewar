/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:45:29 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/07 13:56:00 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	champ_id(t_data *data, int index)
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

int	set_desc_pc(t_data *data)
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
			if (tmp->nb_champ == ptr->reg_number[0])
				tmp->pc = ptr->pc;
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
