/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_by_slowmode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 17:49:58 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/13 19:26:44 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		dump_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < MEM_SIZE)
	{
		while (i++ < 32)
		{
			if (j == (MEM_SIZE - 1))
				ft_printf("%.2hhx", data->map[j++]);
			else
				ft_printf("%.2hhx ", data->map[j++]);
		}
		i = 0;
		write(1, "\n", 1);
	}
	exit(0);
}

static void	first_call_display_map(t_data *data)
{
	werase(data->display->win);
	box(data->display->win, ACS_VLINE, ACS_HLINE);
	print_str(data);
	refresh();
}

int			turn_by_slowmode(t_data *data)
{
	static int	status = 0;
	int			keycode;

	keycode = 0;
	while (42)
	{
		if ((keycode = getch()) == 32)
		{
			if (status == 0)
			{
				first_call_display_map(data);
				status = 1;
			}
			status == 1 ? clear_pc(data) : NULL;
			turn(data);
			status == 1 ? print_pc(data) : NULL;
			(data->cycle)++;
			if ((--(data->cycle_to_die)) <= 0)
				if (verif_end(data) == 1)
					break ;
			init_infos_box(data);
		}
	}
	return (0);
}

int			turn_by_none(t_data *data)
{
	static int	status = 0;

	while (42)
	{
		if (data->flag_visu == 1 && status == 0)
		{
			first_call_display_map(data);
			status = 1;
		}
		data->flag_visu == 1 && status == 1 ? clear_pc(data) : NULL;
		turn(data);
		data->flag_visu == 1 && status == 1 ? print_pc(data) : NULL;
		if (!(data->flag_dump--))
			dump_map(data);
		(data->cycle)++;
		if ((--(data->cycle_to_die)) <= 0)
			if (verif_end(data) == 1)
				break ;
		data->flag_visu == 1 ? init_infos_box(data) : 0;
	}
	return (0);
}
