/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:20:51 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/14 16:28:21 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_list		*copy_elem(t_list *begin, t_list *elem, int pc)
{
	int	j;

	j = -1;
	if (!(begin->prev = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	begin->prev->reg_number = ft_memalloc(sizeof(int) * REG_NUMBER);
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

void		apply_lfork(t_data *data, t_list *elem, unsigned int *params)
{
	short	i;

	i = (short)params[0];
	if (i < 0)
	{
		i %= MEM_SIZE;
		i = MEM_SIZE + i;
	}
	data->begin = copy_elem(data->begin, elem,
		(elem->pc + i) % MEM_SIZE);
	elem->pc = (elem->pc + 3) % MEM_SIZE;
}

void		apply_fork(t_data *data, t_list *elem, unsigned int *params)
{
	short	i;

	i = ((short)(params[0])) % IDX_MOD;
	if (i < 0)
	{
		i %= MEM_SIZE;
		i = MEM_SIZE + i;
	}
	data->begin = copy_elem(data->begin, elem,
		(elem->pc + i) % MEM_SIZE);
	elem->pc = (elem->pc + 3) % MEM_SIZE;
}

void		apply_aff(t_data *data, t_list *elem, unsigned int *param_type,
		unsigned int *params)
{
	char	c;

	(void)param_type;
	(void)params;
	if ((data->map[elem->pc + 2]) < 16)
	{
		c = (elem->reg_number[data->map[elem->pc + 2]]) % 256;
		if (data->flag_visu == 0)
			ft_printf("%c\n", c);
	}
}
