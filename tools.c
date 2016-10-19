/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 12:56:09 by jle-quer          #+#    #+#             */
/*   Updated: 2016/10/19 19:00:52 by jle-quer         ###   ########.fr       */
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

int				find_pc_pos(t_list *list, int *pc, int value)
{
	t_list	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	while (i >= 0)
	{
		if (pc[i] == value)
			return (1);
		i--;
	}
	return (0);
}

static int		*sort_array_pc(int *pc, int len)
{
	int	*tmp;
	int	i;
	int	ref;
	int	cpt;
	int	pos;

	tmp = NULL;
	i = 0;
	cpt = 0;
	pos = 0;
	ref = 0;
	if (!(tmp = (int *)malloc(sizeof(int) * len)))
		return (NULL);
	while (ref < len)
	{
		cpt = pc[i];
		while (i < len)
		{
			if (cpt > pc[i] && pc[i] != -1)
			{
				pos = i;
				cpt = pc[i];
			}
			i++;
		}
		pc[pos] = -1;
		tmp[ref] = cpt;
		ref++;
	}
	free(pc);
	return (tmp);
}

int				*set_array_pc(t_data *data)
{
	t_list	*tmp;
	int		*pc;
	int		i;

	pc = NULL;
	i = 0;
	tmp = data->begin;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (!(pc = (int *)malloc(sizeof(int) * i)))
		return (NULL);
	i = 0;
	tmp = data->begin;
	while (tmp)
	{
		pc[i++] = tmp->pc;
		tmp = tmp->next;
	}
	return (sort_array_pc(pc, i));
}
