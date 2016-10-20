/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 18:27:31 by tbui              #+#    #+#             */
/*   Updated: 2016/10/20 18:27:32 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		apply_ld(t_data *data, t_list *elem, int *params, int *param_types)
{
    //value of first parameter into register
    if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
        elem->reg_number[params[1]] = params[0];// param[0] is the first parameter
    else //maybe divert into an error function of some sorts
    	return ; //I don't think the carry needs to be modified here because in this case the instruction wouldn't have been executed
    //modify carry
    
    //params[1] is the number of the register we need
}
//{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},

int         get_ind_size_at_add(t_data *data, t_list *elem, int prm_pos)
{
    int ind_value;
    char *transfer_bytes;

    //(*prm_pos) = (*prm_pos) + 2;
    ind_value = 0;
    transfer_bytes = get_two_bytes(data, elem, prm_pos); //getting the 2 indirect bytes into a string for transfer, into an int
    ind_value = trans_two_bytes(transfer_bytes); //found in parameters.c
    return (ind_value);
}//getting ind_size bytes at a given address

int 	       	get_reg_size_at_add(t_data *data, t_list *elem, int prm_pos)//prm_pos is the position of the first address byte of the parameter to be searched
{
    int dir_val; //the direct value to be returned
    char *bytes

   	val = 0;
	bytes = get_dir_value_quatre(data, elem, prm_pos);
    val = trans_four_bytes(bytes);
    return (val);

}//this function gets the direct value, whether it's on four or two bytes


void		apply_ldi(t_data *data, t_list *elem, int *param_types, int *params)
{
    int value_one;
    int value_two;
    int S; //value to store into the given register

    if (param_types[0] == DIR_CODE || param_types[0] == IND_CODE)
        value_one =  get_ind_size_at_add(data, elem, params[0] % IDX_MOD); //get value at address
    else if (param_types[0] == REG_CODE)
        value_one =  get_ind_size_at_add(data, elem, elem->reg_number[params[0]] % IDX_MOD); 
    if (param_types[1] == DIR_CODE)
        value_two = params[1]
    else if (param_types[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
 	S = value_one + value_two;
    elem->reg_number[params[2]] = get_reg_size_at_add(data, elem, S % IDX_MOD)//prm_pos is the position of the first address byte of the parameter to be searched
}//{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
//        "load index", 1, 1},

