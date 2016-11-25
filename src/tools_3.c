/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:15:32 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/25 19:18:34 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void			sigkill(int code)
{
	t_display *ptr;

	code = 0;
	ptr = NULL;
	ptr = get_dsp_struct_addr(NULL);
	delete_win(ptr);
	exit(0);
}

void			delete_win(t_display *display)
{
	if (display->info)
		delwin(display->info);
	if (display->win)
		delwin(display->win);
	if (display->header)
		delwin(display->header);
	if (display->screen)
		delwin(display->screen);
	clear();
	refresh();
	endwin();
}

t_display		*get_dsp_struct_addr(t_display *dsp)
{
	static	t_display	*tmp = NULL;

	if (dsp)
		tmp = dsp;
	return (tmp);
}

int				champ_id(t_data *data, int index)
{
	t_desc		*tmp;

	set_desc_pc(data);
	tmp = data->desc;
	while (tmp)
	{
		if (index >= tmp->pc && index < tmp->pc + (int)tmp->size)
			return (tmp->nb_champ);
		tmp = tmp->next;
	}
	return (-1);
}

unsigned char	*get_str_addr(unsigned char *mem)
{
	static unsigned char		*ptr = NULL;

	if (mem)
		ptr = mem;
	return (ptr);
}
