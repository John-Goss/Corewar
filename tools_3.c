/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vijacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:18:43 by vijacque          #+#    #+#             */
/*   Updated: 2016/11/25 15:21:18 by vijacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int						champ_id(t_data *data, int index)
{
	t_desc		*tmp;

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

unsigned char			*get_str_addr(unsigned char *mem)
{
	static unsigned char		*ptr = NULL;

	if (mem)
		ptr = mem;
	return (ptr);
}
