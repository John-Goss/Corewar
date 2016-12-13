/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:45:11 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/13 19:09:55 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	move_pc_bad_registers(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_types)
{
	elem->pc = (elem->pc + data->dep) % MEM_SIZE;
	free_params(params, param_types);
}

void	exec_no_ocp(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_types)
{
	instr_no_ocp(data, elem, params);
	free_params(params, param_types);
}
