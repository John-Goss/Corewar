/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:21:53 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/14 16:28:42 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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
	if (((param_types[0] == DIR_CODE || param_types[0] == IND_CODE ||
					param_types[0] == REG_CODE) &&
				(param_types[1] == DIR_CODE ||
				param_types[1] == REG_CODE)) && params[2] < 16)
	{
		if (param_types[0] == DIR_CODE)
			value_one = (short)params[0];
		else if (param_types[0] == IND_CODE)
			value_one = recup_ind(data, (short)params[0], elem->pc);
		else if (param_types[0] == REG_CODE && params[0] < 16)
			value_one = elem->reg_number[params[0]];
		if (param_types[1] == DIR_CODE)
			value_two = (short)params[1];
		else if (param_types[1] == REG_CODE && params[1] < 16)
			value_two = elem->reg_number[params[1]];
		s = (value_one + value_two) % IDX_MOD;
		elem->reg_number[params[2]] = recup_ind(data, (short)s, elem->pc);
	}
}

void	apply_ld(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_type)
{
	int	i;

	i = 0;
	if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
	{
		if (param_type[0] == DIR_CODE)
			i = (int)params[0];
		if (param_type[0] == IND_CODE)
			i = recup_ind(data, ((short)(params[0])) % IDX_MOD, elem->pc);
		if (params[1] < 16)
			elem->reg_number[params[1]] = i;
		if (params[0] == 0)
			elem->carry = 1;
		else
			elem->carry = 0;
	}
}
