/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:20:57 by tbui              #+#    #+#             */
/*   Updated: 2016/11/09 17:21:44 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

t_list *copy_elem(t_list *begin, t_list *elem, int pc)
{
	int	j;

	j = -1;
	if (!(begin->prev = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	begin->prev->reg_number = ft_memalloc(REG_NUMBER * sizeof(int));
	while (j++ != REG_NUMBER)
		begin->prev->reg_number[j] = elem->reg_number[j];
	begin->prev->prev = NULL;
	begin->prev->next = begin;
	begin->prev->pc = pc;
	begin->prev->process_nb = (begin->process_nb) + 1;
	begin->prev->action_time = 0;
	begin->prev->carry = elem->carry;
	begin->prev->live = elem->live;
	begin->prev->nb_champ = elem->nb_champ;
	begin->prev->dir_by = -1;
	return (begin->prev);
}

void		apply_lfork(t_data *data, t_list *elem)// I need param
{
//	data->begin = copy_elem(data->begin, elem, elem->pc +
//			(params[0] % MEM_SIZE));
	data->begin = create_elem(data->begin, elem->reg_number[0], elem->pc +
			(data->map[(elem->pc + 1) % MEM_SIZE]));
	elem->pc = (elem->pc + 3) % MEM_SIZE;
}

void      apply_fork(t_data *data, t_list *elem)// I need param too
{
//	data->begin = copy_elem(data->begin, elem, elem->pc +
//			(params[0] % IDX_MOD));
	data->begin = create_elem(data->begin, elem->reg_number[0], elem->pc +
			(data->map[(elem->pc + 1) % IDX_MOD]));
	elem->pc = (elem->pc + 3) % MEM_SIZE;
}


void		apply_aff(t_data *data, t_list *elem, unsigned int *params)
{
	char	c;

	c = (elem->reg_number[data->map[elem->pc + 2]])  % 256;
	ft_printf("%c", c);
	elem->pc += 3;
}
