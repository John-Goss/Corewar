/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 12:56:09 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/16 17:21:33 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	*get_str_addr(unsigned char *mem)
{
	static unsigned char	*ptr = NULL;

	if (mem)
		ptr = mem;
	return (ptr);
}

WINDOW			*get_win_addr(WINDOW *window)
{
	static WINDOW	*ptr = NULL;

	if (window)
		ptr = window;
	return (ptr);
}

t_display		*get_dsp_struct_addr(t_display *dsp)
{
	static t_display	*tmp = NULL;

	if (dsp)
		tmp = dsp;
	return (tmp);
}

int				nb_champ_pc(t_list *list, int value)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->pc == value)
			return (tmp->nb_champ); // NE PAS LAISSER SUR REG_NUMBER A PASSER SUR begin->pid !!!
		tmp = tmp->next;
	}
	return (-1);
}

int				find_pc_pos(t_list *list, int *pc, int nb_champ, int value)
{
	t_list	*tmp;
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	tmp = list;
	while (tmp)
	{
		cpt++;
		tmp = tmp->next;
	}
	while (i < cpt)
	{
		if (pc[i] == value)
			return (nb_champ_pc(list, value));
		i++;
	}
	return (-1);
}

int				*set_array_pc(t_list *list_pc)
{
	t_list	*tmp;
	int		*pc;
	int		i;

	pc = NULL;
	i = 0;
	tmp = list_pc;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (!(pc = (int *)malloc(sizeof(int) * i)))
		return (NULL);
	tmp = list_pc;
	i = 0;
	while (tmp)
	{
		pc[i++] = tmp->pc;
		tmp = tmp->next;
	}
	return (pc);
}
