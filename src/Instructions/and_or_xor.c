/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:19:25 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/14 16:28:04 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	apply_and(t_data *data, t_list *elem, unsigned int *params,
			unsigned int *param_type)
{
	int	value_one;
	int	value_two;

	value_one = 0;
	value_two = 0;
	if (params[2] > 15)
		return ;
	if (param_type[0] == REG_CODE && params[0] < 16)
		value_one = elem->reg_number[params[0]];
	else if (param_type[0] == DIR_CODE)
		value_one = (int)params[0];
	else if (param_type[0] == IND_CODE)
		value_one = recup_ind(data, (short)params[0], elem->pc);
	if (param_type[1] == REG_CODE && params[1] < 16)
		value_two = elem->reg_number[params[1]];
	else if (param_type[1] == DIR_CODE)
		value_two = (int)params[1];
	else if (param_type[1] == IND_CODE)
		value_two = recup_ind(data, (short)params[1], elem->pc);
	elem->reg_number[params[2]] = value_one & value_two;
	if (elem->reg_number[params[2]] == 0)
		elem->carry = 1;
	else
		elem->carry = 0;
}

void	apply_or(t_data *data, t_list *elem, unsigned int *params,
			unsigned int *param_type)
{
	int value_one;
	int value_two;

	value_one = 0;
	value_two = 0;
	if (params[2] > 15)
		return ;
	if (param_type[0] == REG_CODE && params[0] < 16)
		value_one = elem->reg_number[params[0]];
	else if (param_type[0] == DIR_CODE)
		value_one = (int)params[0];
	else if (param_type[0] == IND_CODE)
		value_one = recup_ind(data, (short)params[0], elem->pc);
	if (param_type[1] == REG_CODE && params[1] < 16)
		value_two = elem->reg_number[params[1]];
	else if (param_type[1] == DIR_CODE)
		value_two = (int)params[1];
	else if (param_type[1] == IND_CODE)
		value_two = recup_ind(data, (short)params[1], elem->pc);
	elem->reg_number[params[2]] = value_one | value_two;
	if (elem->reg_number[params[2]] == 0)
		elem->carry = 1;
	else
		elem->carry = 0;
}

void	apply_xor(t_data *data, t_list *elem, unsigned int *params,
			unsigned int *param_type)
{
	int	value_one;
	int	value_two;

	value_one = 0;
	value_two = 0;
	if (params[2] > 15)
		return ;
	if (param_type[0] == REG_CODE && params[0] < 16)
		value_one = elem->reg_number[params[0]];
	else if (param_type[0] == DIR_CODE)
		value_one = (int)params[0];
	else if (param_type[0] == IND_CODE)
		value_one = recup_ind(data, (short)params[0], elem->pc);
	if (param_type[1] == REG_CODE && params[1] < 16)
		value_two = elem->reg_number[params[1]];
	else if (param_type[1] == DIR_CODE)
		value_two = (int)params[1];
	else if (param_type[1] == IND_CODE)
		value_two = recup_ind(data, (short)params[1], elem->pc);
	elem->reg_number[params[2]] = value_one ^ value_two;
	if (elem->reg_number[params[2]] == 0)
		elem->carry = 1;
	else
		elem->carry = 0;
}
