/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:20:57 by tbui              #+#    #+#             */
/*   Updated: 2016/10/21 16:04:28 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		apply_lfork(t_data *data, t_list *elem)
{
	data->begin = create_elem(data->begin, elem->reg_number[0], elem->pc +
			(data->map[(elem->pc + 1) % MEM_SIZE]));
	elem->pc = (elem->pc + 2) % MEM_SIZE;
}

void      apply_fork(t_data *data, t_list *elem)
{
	data->begin = create_elem(data->begin, elem->reg_number[0], elem->pc +
			(data->map[(elem->pc + 1) % MEM_SIZE]) % IDX_MOD);
	elem->pc = (elem->pc + 2) % MEM_SIZE;
}


void		apply_aff(t_data *data, t_list *elem, unsigned int *params)
{



}//{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	//{0, 0, {0}, 0, 0, 0, 0, 0}
