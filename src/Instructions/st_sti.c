/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:23:17 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/06 17:07:55 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	put_in_bytes(t_data *data, t_list *elem, int address, int reg_value)
{
	char	byte_array[4];
	int		i;
	int		index;
	int		tmp;

	i = -1;
	if (address < 0 && elem->pc < -address)
		address = MEM_SIZE + (elem->pc + address);
	byte_array[0] = (reg_value >> 24) & 0xFF;
	byte_array[1] = (reg_value >> 16) & 0xFF;
	byte_array[2] = (reg_value >> 8) & 0xFF;
	byte_array[3] = reg_value & 0xFF;
	tmp = ((elem->pc + address)) % MEM_SIZE;
	data->map[tmp] = byte_array[0];
	data->map[(tmp + 1) % MEM_SIZE] = byte_array[1];
	data->map[(tmp + 2) % MEM_SIZE] = byte_array[2];
	data->map[(tmp + 3) % MEM_SIZE] = byte_array[3];
	if (data->flag_visu == 1)
	{
		while (++i < 4)
		{
			index = (tmp + i) % MEM_SIZE;
			print_index(data, elem, index);
		}
	}
}

/*
** this function puts the desired value onto the required number of bytes in
** the memory.
** getting the value at the address which we've determined by combining the
** values of the last two parameters.
** then putting the value we found at that address into
** the register, given to us in the first parameter.
*/

void	apply_sti(t_data *data, t_list *elem, unsigned int *param_types,
		unsigned int *params)
{
	int	value_one;
	int	value_two;
	int	address;

	address = 0;
	value_one = 0;
	value_two = 0;
	if (param_types[1] == DIR_CODE || param_types[1] == IND_CODE)
		value_one = params[1];
	else if (param_types[0] == REG_CODE)
		value_one = elem->reg_number[params[1]];
	if (param_types[2] == DIR_CODE)
		value_two = params[2];
	else if (param_types[2] == REG_CODE)
		value_two = elem->reg_number[params[2]];
	address = (value_one + value_two);
	put_in_bytes(data, elem, address, elem->reg_number[params[0]]);
}

/*
** this takes the value of a register and STORES it at either an address
** or another register.
*/

void	apply_st(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_types)
{
	int i;

	i = ((int)params[1]) % IDX_MOD;
	if (param_types[1] == IND_CODE)
		put_in_bytes(data, elem, (i - elem->pc),
				elem->reg_number[params[0]]);
	else if (param_types[1] == REG_CODE)
		elem->reg_number[i] = elem->reg_number[params[0]];
}
