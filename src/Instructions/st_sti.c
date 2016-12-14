/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:23:17 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/14 16:30:52 by jle-quer         ###   ########.fr       */
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
	byte_array[0] = (reg_value >> 24) & 0xFF;
	byte_array[1] = (reg_value >> 16) & 0xFF;
	byte_array[2] = (reg_value >> 8) & 0xFF;
	byte_array[3] = reg_value & 0xFF;
	tmp = (elem->pc + address) % MEM_SIZE;
	data->map[tmp % MEM_SIZE] = byte_array[0];
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
	if (param_types[1] == IND_CODE)
		value_one = recup_ind(data, (short)params[1], elem->pc);
	else if (param_types[1] == DIR_CODE)
		value_one = (short)params[1];
	else if (param_types[1] == REG_CODE && params[1] < 16)
		value_one = elem->reg_number[params[1]];
	if (param_types[2] == DIR_CODE)
		value_two = (short)params[2];
	else if (param_types[2] == REG_CODE && params[2] < 16)
		value_two = elem->reg_number[params[2]];
	address = (value_one + value_two) % IDX_MOD;
	if (address < 0)
	{
		address %= MEM_SIZE;
		address = MEM_SIZE + address;
	}
	if (params[0] < 16)
		put_in_bytes(data, elem, address, elem->reg_number[params[0]]);
}

/*
** this takes the value of a register and STORES it at either an address
** or another register.
*/

void	apply_st(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_types)
{
	int		i;

	if (param_types[1] == IND_CODE && params[0] < 16)
	{
		i = ((short)params[1]) % IDX_MOD;
		if (i < 0)
		{
			i %= MEM_SIZE;
			i = MEM_SIZE + i;
		}
		put_in_bytes(data, elem, i, elem->reg_number[params[0]]);
	}
	else if (param_types[1] == REG_CODE && params[0] < 16 && params[1] < 16)
	{
		elem->reg_number[params[1]] = elem->reg_number[params[0]];
	}
}

int		recup_ind(t_data *data, short tmp, int pc)
{
	int	i;

	tmp = tmp % IDX_MOD;
	if (tmp < 0 && pc < -(tmp))
	{
		tmp %= MEM_SIZE;
		tmp = MEM_SIZE + (tmp);
	}
	tmp += pc;
	i = (data->map[tmp % MEM_SIZE] << 24 & 0xff000000) |
	(data->map[(tmp + 1) % MEM_SIZE] << 16 & 0xff0000) |
	(data->map[(tmp + 2) % MEM_SIZE] << 8 & 0xff00) |
	(data->map[(tmp + 3) % MEM_SIZE] & 0xff);
	return (i);
}
