/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 12:01:01 by lbaudran          #+#    #+#             */
/*   Updated: 2016/10/20 17:36:35 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//Finish coding all the unfinished functions
//find out how to direct the process into the given instruction
//test and refactor EVERYTHING!
//manage both idxd and un-idxd values in the instructions
//refactor all instructions
//find out how to copy a process and then have it run along with the other one

void        instr_no_ocp(t_data *data, t_list *elem)
{
    if (data->map[elem->pc] == 0x0C)  
       //fork
    else if (data->map[elem->pc] == 0x01)
       apply_live(data, elem);   
    else if (data->map[elem->pc] == 0x09)
        //zjmp    0
}

void         instr_w_ocp(t_data *data, t_list *elem, int *params, int *param_types);
{
    else if (data->map[elem->pc] == 0x02)
        apply_ld(data, elem, params);
    else if (data->map[elem->pc] == 0x03)
        apply_st(data, elem, params, param_types);
    else if (data->map[elem->pc] == 0x04)
        apply_add(data, elem);
    else if (data->map[elem->pc] == 0x05)
        apply_sub(data, elem);
    else if (data->map[elem->pc] == 0x06)
        apply_and(data, elem, params, param_types);
    else if (data->map[elem->pc] == 0x07)
        apply_or(data, elem, params, param_types);
    else if (data->map[elem->pc] == 0x08)
        apply_xor(data, elem, params, param_types);
    else if (data->map[elem->pc] == 0x10)
        //aff
    else if (data->map[elem->pc] == 0x0A)
        //ldi
    else if (data->map[elem->pc] == 0x0B)
        //sti
    else if (data->map[elem->pc] == 0x0E)
        //lldi
    else if (data->map[elem->pc] == 0x0F)
        //lfork
    else if (data->map[elem->pc] == 0x0D)
        //lld
}

void		apply_live(t_data *data, t_list *elem)
{
	t_desc	*desc;
	int		nb_champ;
	int		i;

	nb_champ = (data->map[(elem->pc + 1) % MEM_SIZE] << 24 & 0xff000000) |
	(data->map[(elem->pc + 2) % MEM_SIZE] << 16 & 0xff0000) |
	(data->map[(elem->pc + 3) % MEM_SIZE] << 8 & 0xff00) |
	(data->map[(elem->pc + 4) % MEM_SIZE] & 0xff);

	elem->pc = (elem->pc + 5) % MEM_SIZE;
	data->live_cpt++;
	while (desc)
	{
		if (nb_champ == desc->nb_champ)
			data->last_live_nb_champ = nb_champ;
		desc = desc->next;
	}
}

void		apply_st(t_data *data, t_list *elem, int *params, int *param_types)
{

    if (param_types[1] == IND_CODE)//go to the address (PC plus value) and store first value
        data->map[params[1]] =  elem->reg_number[params[0]]; //value to copy into the other place
    else if (param_types[1] == REG_CODE)//put the value to be copied into the register
        elem->reg_number[params[1]] = elem->reg_number[params[0]]; //value to copy into the other place
}//this takes the value of a register and STORES it at either an address or another register


//takes two paramters of which the third will always be register
void		apply_and(t_data *data,t_list *elem, int *param, int *param_types)
{
    unsigned int value_one; //param values
    unsigned int value_two;

    if (params_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (params_type[0] == DIR_CODE)
        value_one = params[0];
    else if (params_type[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    if (params_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (params_type[1] == DIR_CODE)
        value_two = params[1];
    else if (params_type[1] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    elem->reg_number[params[2]] = value_one & value_two;//so now we got the two values which we need to stock
}//the bit operation & is executed on the first two and then stored at the third which is a register

void		apply_or(t_data *data, t_list *elem)
{
    unsigned int value_one; //param values
    unsigned int value_two;

    if (params_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (params_type[0] == DIR_CODE)
        value_one = params[0];
    else if (params_type[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    if (params_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (params_type[1] == DIR_CODE)
        value_two = params[1];
    else if (params_type[1] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    elem->reg_number[params[2]] = value_one | value_two;
}

void		apply_xor(t_data *data, t_list *elem)
{
    unsigned int value_one; //param values
    unsigned int value_two;

    if (params_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (params_type[0] == DIR_CODE)
        value_one = params[0];
    else if (params_type[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    if (params_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (params_type[1] == DIR_CODE)
        value_two = params[1];
    else if (params_type[1] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    elem->reg_number[params[2]] = value_one ^ value_two;


}

void		apply_zjmp(t_data *data, t_list *elem, int *params)
{
    if (elem->carry == 1)
            elem->pc = (elem->pc + (params[0] % IDX_MOD)) % MEM_SIZE;
}

void		apply_ldi(t_data *data, t_list *elem, int *param_types, int *params)
{
    int value_one;
    int value_two;
    int store; //value to store into the given register

    if (param_types[0] == DIR_CODE)
        value_one = params[0];
    else if (param_types[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    else if (param_types[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    if (param_types[1] == DIR_CODE)
        value_two = params[1]
    else if (param_types[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    store = get_ind_value_idxd(value_one + value_two);
    elem->reg_number[params[2]] = store;

}//{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
//        "load index", 1, 1},



void		apply_lld(t_data *data, t_list *elem) //addresses not relative to IDX
{
      if (param_type[0] == DIR_CODE)
        elem->reg_number[params[1]] = params[0];// param[0] is the first parameter
    else if (param_type[0] == IND_CODE)
        elem->reg_number[params[1]] = get_ind_value(params[0]);
    else if (param_types[0] == REG_CODE)
        elem->reg_number[params[1]] = elem->reg_number[params[0]];
}

void		apply_lldi(t_data *data, t_list *elem) //addresses not relative to IDX
{

    int value_one;
    int value_two;
    int store; //value to store into the given register

    if (param_types[0] == DIR_CODE)
        value_one = params[0];
    else if (param_types[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    else if (param_types[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    if (param_types[1] == DIR_CODE)
        value_two = params[1]
    else if (param_types[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    store = get_ind_value_idxd(value_one + value_two);
    elem->reg_number[params[2]] = store;
    //figure out carry modification
}

void		apply_lfork(t_data *data, t_list *elem)
{
	data->begin = create_elem(data->begin, elem->reg_number[0], pc +
			(data->map[(elem->pc + 1) % MEM_SIZE]));
	elem->pc = (elem->pc + 2) % MEM_SIZE;
}

void		apply_aff(t_data *data, t_list *elem)
{
//IDK what the fuck this means
}


void      apply_fork(t_data *data, t_list *elem)
{
	data->begin = create_elem(data->begin, elem->reg_number[0], pc +
			(data->map[(elem->pc + 1) % MEM_SIZE]) % IDX_MOD);
	elem->pc = (elem->pc + 2) % MEM_SIZE;
}



void        instruction_exec(t_data *data, t_list *elem)
{
    int *param_types;
    unsigned int *params;
    char opc; //DO NOT CONFUSE WITH OCP!!!

    //THE PC IS ON THE OPC AT THIS POINT
    opc = data->map[(elem->pc) % MEM_SIZE];
    param_types = det_types(data->map[(elem->pc) % MEM_SIZE]);
    params = get_params(param_types, data, elem);
    if (opc == 0x0C || opc == 0x09 || opc == 0x01)
    {
        instr_no_ocp(data, elem, params);
        return ; //free all the shit first dude
    }
    instr_w_ocp(data, elem, params, param_types);        
}
