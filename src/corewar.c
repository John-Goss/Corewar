/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:55:01 by lbaudran          #+#    #+#             */
/*   Updated: 2016/12/13 17:11:59 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			main(int argc, char **argv)
{
	t_data	data;

	init_structur(&data);
	check_flag(argc, argv, &data);
	parse_map(argc, argv, &data);
	if (data.flag_visu == 1)
	{
		get_str_addr(data.map);
		aff_window(&data);
	}
	data.flag_slowmode == 1 ? turn_by_slowmode(&data) : turn_by_none(&data);
	end(&data);
	return (0);
}

void		adjust_action_time(t_list *elem, char pc)
{
	if (pc == 0x01 || pc == 0x04 || pc == 0x05 || pc == 0x0D)
		elem->action_time = 10;
	else if (pc == 0x02 || pc == 0x03)
		elem->action_time = 5;
	else if (pc == 0x06 || pc == 0x07 || pc == 0x08)
		elem->action_time = 6;
	else if (pc == 0x0A || pc == 0x0B)
		elem->action_time = 25;
	else if (pc == 0x09)
		elem->action_time = 20;
	else if (pc == 0x0C)
		elem->action_time = 800;
	else if (pc == 0x0E)
		elem->action_time = 50;
	else if (pc == 0x0F)
		elem->action_time = 1000;
	else if (pc == 0x10)
		elem->action_time = 2;
}

void		process_action(t_data *data, t_list *elem)
{
	if ((!(data->map[elem->pc] >= 0x01 && data->map[elem->pc] <= 0x10)) &&
			!elem->action_time)
	{
		elem->pc++;
		elem->pc = elem->pc % MEM_SIZE;
		return ;
	}
	else
	{
		if (!(elem->action_time))
			adjust_action_time(elem, data->map[elem->pc]);
		if (elem->action_time)
		{
			elem->action_time--;
			if (!(elem->action_time))
				instruction_exec(data, elem);
		}
	}
}

void		turn(t_data *data)
{
	t_list *elem;

	if (data == NULL || data->begin == NULL)
		return ;
	elem = data->begin;
	while (elem)
	{
		process_action(data, elem);
		elem = elem->next;
	}
	return ;
}
