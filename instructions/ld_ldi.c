/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 18:27:31 by tbui              #+#    #+#             */
/*   Updated: 2016/11/17 13:30:25 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		get_ind_size_at_add(t_data *data, t_list *elem, int prm_pos)
{
	int ind_value;
	char *transfer_bytes;

	ind_value = 0;
	transfer_bytes = get_two_bytes(data, elem, prm_pos); //getting the 2 indirect bytes into a string for transfer, into an int
	ind_value = trans_two_bytes(transfer_bytes); //found in parameters.c
	return (ind_value);
}//getting ind_size bytes at a given address

int		get_reg_size_at_add(t_data *data, t_list *elem, int prm_pos)//prm_pos is the position of the first address byte of the parameter to be searched
{
	int val; //the direct value to be returned
	char *bytes;

	val = 0;
	bytes = get_dir_value_quatre(data, elem, prm_pos);
	val = trans_four_bytes(bytes);
	return (val);

}//this function gets the direct value, whether it's on four or two bytes


void	apply_ldi(t_data *data, t_list *elem, unsigned int *param_types,
		unsigned int *params)
{
	int	value_one;
	int	value_two;
	int	S; //value to store into the given register

	value_one = 0;
	value_two = 0;
	S = 0;
	if (param_types[0] == DIR_CODE || param_types[0] == IND_CODE)
		value_one =  get_ind_size_at_add(data, elem, params[0] % IDX_MOD); //get value at address
	else if (param_types[0] == REG_CODE)
		value_one = get_ind_size_at_add(data, elem, elem->reg_number[params[0]]
				% IDX_MOD);
	if (param_types[1] == DIR_CODE)
		value_two = params[1];
	else if (param_types[1] == REG_CODE)
		value_two = elem->reg_number[params[1]];
	S = value_one + value_two;
	elem->reg_number[params[2]] = get_reg_size_at_add(data, elem, S % IDX_MOD);//prm_pos is the position of the first address byte of the parameter to be searched
}//{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
//        "load index", 1, 1},

void	apply_ld(t_data *data, t_list *elem, unsigned int *params, unsigned int *param_type)
{
	//value of first parameter into register
	DEBUGG;
	dprintf(open("/dev/ttys003", 1), "Param_type [%d] - DIR_CODE == [%d] - IND_CODE == [%d]\n\n", param_type[0], DIR_CODE, IND_CODE);
	if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
	{
		DEBUGG;
		dprintf(open("/dev/ttys003", 1), "Charged Value [%d] - reg number index [%d]\n\n", params[0], params[1]);
		elem->reg_number[params[1]] = params[0];// param[0] is the first parameter
		if (elem->carry)
			elem->carry = 0;
		else if (!elem->carry)
			elem->carry = 1;
	}
	else
	{
		elem->pc++; // VRAIMENT ?
		return ;
	}
	//params[1] is the vnumber of the register we need
}
