/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 18:12:34 by tbui              #+#    #+#             */
/*   Updated: 2016/11/17 13:45:26 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	put_in_bytes(t_data *data,t_list *elem, int address, int reg_value)
{
	char	byte_array[4];

	byte_array[0] = (reg_value >> 24) & 0xFF;
	byte_array[1] = (reg_value >> 16) & 0xFF;
	byte_array[2] = (reg_value >> 8) & 0xFF;
	byte_array[3] = reg_value & 0xFF;
	data->map[(elem->pc + (address % IDX_MOD))] = byte_array[0];
	data->map[(elem->pc + ((address + 1) % IDX_MOD))] = byte_array[1];
	data->map[(elem->pc + ((address + 2) % IDX_MOD))] = byte_array[2];
	data->map[(elem->pc + ((address + 3) % IDX_MOD))] = byte_array[3];
}

void	apply_sti(t_data *data, t_list *elem, unsigned int *param_types, unsigned int *params)
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
	address = value_one + value_two;
	put_in_bytes(data, elem, address, elem->reg_number[params[0]]);//this function puts the desired value onto the required number of bytes in the memory

	//getting the value at the address which we've determined by combining the values of the last two parameters
	//then putting the value we found at that address into the register, given to us in the first parameter
}

void	apply_st(t_data *data, t_list *elem, unsigned int *params, unsigned int *param_types)
{
	if (param_types[1] == IND_CODE)//go to the address (PC plus value) and store first value
		put_in_bytes(data, elem, (params[1] - elem->pc) % IDX_MOD, elem->reg_number[params[0]]);
	//        data->map[(params[1] % IDX_MOD) % MEM_SIZE] =  elem->reg_number[params[0]]; //value to copy into the other place
	else if (param_types[1] == REG_CODE)//put the value to be copied into the register
		elem->reg_number[params[1]] = elem->reg_number[params[0]]; //value to copy into the other place
}//this takes the value of a register and STORES it at either an address or another register
