/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:21:25 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/13 19:06:34 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	instr_no_ocp(t_data *data, t_list *elem, unsigned int *params)
{
	if (data->map[elem->pc] == 0x0C)
		apply_fork(data, elem, params);
	else if (data->map[elem->pc] == 0x01)
		apply_live(data, elem);
	else if (data->map[elem->pc] == 0x09)
		apply_zjmp(data, elem, params);
	else if (data->map[elem->pc] == 0x0F)
		apply_lfork(data, elem, params);
}

void	instr_w_ocp(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_types)
{
	if (data->map[elem->pc] == 0x02)
		apply_ld(data, elem, params, param_types);
	else if (data->map[elem->pc] == 0x03)
		apply_st(data, elem, params, param_types);
	else if (data->map[elem->pc] == 0x04)
		apply_add(data, elem, params, param_types);
	else if (data->map[elem->pc] == 0x05)
		apply_sub(data, elem, params, param_types);
	else if (data->map[elem->pc] == 0x06)
		apply_and(data, elem, params, param_types);
	else if (data->map[elem->pc] == 0x07)
		apply_or(data, elem, params, param_types);
	else if (data->map[elem->pc] == 0x08)
		apply_xor(data, elem, params, param_types);
	else if (data->map[elem->pc] == 0x0A)
		apply_ldi(data, elem, param_types, params);
	else if (data->map[elem->pc] == 0x0B)
		apply_sti(data, elem, param_types, params);
	else if (data->map[elem->pc] == 0x0E)
		apply_lldi(data, elem, param_types, params);
	else if (data->map[elem->pc] == 0x0D)
		apply_lld(data, elem, param_types, params);
	else if (data->map[elem->pc] == 0x10)
		apply_aff(data, elem, param_types, params);
}

int		protect_registers(unsigned int *params, unsigned int *param_types)
{
	int	k;

	k = 0;
	while (param_types[k])
	{
		if (param_types[k] == REG_CODE)
			params[k] = params[k] - 1;
		if (param_types[k] == REG_CODE && params[k] > 15)
			return (0);
		k++;
	}
	return (1);
}

/*
** Do not confuse opc with ocp.
*/

void	instruction_exec(t_data *data, t_list *elem)
{
	unsigned int	*parameters[2];
	char			opc;
	int				tmp;

	tmp = elem->pc;
	data->dep = 0;
	opc = data->map[(elem->pc) % MEM_SIZE];
	parameters[0] = det_types(data, elem, data->map[(elem->pc + 1) % MEM_SIZE]);
	parameters[1] = get_params(parameters[0], data, elem);
	if ((int)parameters[0][0] == -1)
		return ;
	if (protect_registers(parameters[1], parameters[0]) == 0)
	{
		move_pc_bad_registers(data, elem, parameters[1], parameters[0]);
		return ;
	}
	if (opc == 0x0C || opc == 0x09 || opc == 0x01 || opc == 0x10 || opc == 0x0F)
	{
		exec_no_ocp(data, elem, parameters[1], parameters[0]);
		tmp == elem->pc ? (elem->pc = (elem->pc + data->dep) % MEM_SIZE) : 0;
		return ;
	}
	instr_w_ocp(data, elem, parameters[1], parameters[0]);
	elem->pc = (elem->pc + data->dep) % MEM_SIZE;
	free_params(parameters[1], parameters[0]);
}

void	free_params(unsigned int *to_free, unsigned int *to_free_2)
{
	if (to_free)
		free(to_free);
	if (to_free_2)
		free(to_free_2);
}
