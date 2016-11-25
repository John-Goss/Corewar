/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 18:27:31 by tbui              #+#    #+#             */
/*   Updated: 2016/11/25 12:57:37 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		get_ind_size_at_add(t_data *data, t_list *elem, int prm_pos)
{
	int		ind_value;
	char	*transfer_bytes;

	ind_value = 0;
	transfer_bytes = get_two_bytes(data, elem, prm_pos);
	ind_value = trans_two_bytes(transfer_bytes);
	return (ind_value);
}

/*
** this function gets the direct value, whether it's on four or two bytes.
*/

int		get_reg_size_at_add(t_data *data, t_list *elem, int prm_pos)
{
	int		val;
	char	*bytes;

	val = 0;
	bytes = get_dir_value_quatre(data, elem, prm_pos);
	val = trans_four_bytes(bytes);
	return (val);
}

void	apply_ldi(t_data *data, t_list *elem, unsigned int *param_types,
		unsigned int *params)
{
	int	value_one;
	int	value_two;
	int	s;

	value_one = 0;
	value_two = 0;
	s = 0;
	if (param_types[0] == DIR_CODE || param_types[0] == IND_CODE)
		value_one = get_ind_size_at_add(data, elem, params[0] % IDX_MOD);
	else if (param_types[0] == REG_CODE)
		value_one = get_ind_size_at_add(data, elem, elem->reg_number[params[0]]
				% IDX_MOD);
	if (param_types[1] == DIR_CODE)
		value_two = params[1];
	else if (param_types[1] == REG_CODE)
		value_two = elem->reg_number[params[1]];
	s = value_one + value_two;
	elem->reg_number[params[2]] = get_reg_size_at_add(data, elem, s % IDX_MOD);
}

void	apply_ld(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_type)
{
	if (elem->carry)
		elem->carry = 0;
	else if (!elem->carry)
		elem->carry = 1;
	if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
	{
		if (params[1] < 16)
			elem->reg_number[params[1]] = params[0];
	}
	else
		elem->pc = (elem->pc + 1) % MEM_SIZE;
}
