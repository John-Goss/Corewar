/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 12:01:01 by lbaudran          #+#    #+#             */
/*   Updated: 2016/11/01 16:41:48 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

//Finish coding apply_aff
//find out how to direct the process into the given instruction
//test and refactor EVERYTHING!
//refactor all instructions
//figure how the carry modifications work, and what it means to "modify the carry" do we always put it to 1?

void        instr_no_ocp(t_data *data, t_list *elem, unsigned int *params)
{
    if (data->map[elem->pc] == 0x0C)  
        apply_fork(data, elem);
    else if (data->map[elem->pc] == 0x01)
       apply_live(data, elem);   
    else if (data->map[elem->pc] == 0x09)
        apply_zjmp(data, elem, params);
    else if (data->map[elem->pc] == 0x0F)
        apply_lfork(data, elem);
    else if (data->map[elem->pc] == 0x10)
        apply_aff(data, elem, params);
}

void         instr_w_ocp(t_data *data, t_list *elem, unsigned int *params, unsigned int *param_types)
{
    if (data->map[elem->pc] == 0x02)
        apply_ld(data, elem, params, param_types);
    else if (data->map[elem->pc] == 0x03)
        apply_st(data, elem, params, param_types);
    else if (data->map[elem->pc] == 0x04)
        apply_add(data, elem, params, param_types);
    else if (data->map[elem->pc] == 0x05)
        apply_sub(data, elem, params,param_types);
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
}

void        instruction_exec(t_data *data, t_list *elem)
{
    unsigned int *param_types;
    unsigned int *params;
    char opc; //DO NOT CONFUSE WITH OCP!!!

    //THE PC IS ON THE OPC AT THIS POINT
    opc = data->map[(elem->pc) % MEM_SIZE];
    param_types = det_types(data->map[(elem->pc + 1) % MEM_SIZE]);
    params = get_params(param_types, data, elem);
    if (opc == 0x0C || opc == 0x09 || opc == 0x01)
    {
        instr_no_ocp(data, elem, params);
        return ; //free all the shit first dude
    }
    instr_w_ocp(data, elem, params, param_types);
}
