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
        apply_fork(data, elem, params);
    else if (data->map[elem->pc] == 0x01)
       apply_live(data, elem);   
    else if (data->map[elem->pc] == 0x09)
        apply_zjmp(data, elem, params);
    else if (data->map[elem->pc] == 0x0F)
        apply_lfork(data, elem, params);
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


int protect_registers(unsigned int *params, unsigned int *param_types)
{
    int k;

    k = 0;
    while (param_types[k])
    {
        if (param_types[k] == REG_CODE && params[k] == 42)
            return (0); //0 implies error case. move the PC but don't execute the instruction
        k++;
    }
    return (1); //means either no registers have been found, or no registers have been marked as an error. C'est bon
}//goes through the params array and sees if it's a register. if yes then it will chck if its value is 42    


void        instruction_exec(t_data *data, t_list *elem)
{
    unsigned int *param_types;
    unsigned int *params;
    char opc; //DO NOT CONFUSE WITH OCP!!!
    int elem_tmp;

    elem_tmp = elem->pc;
    data->dep = 0;
    opc = data->map[(elem->pc) % MEM_SIZE];
    param_types = det_types(data, elem, data->map[(elem->pc + 1) % MEM_SIZE]);
    params = get_params(param_types, data, elem);
    if (protect_registers(params, param_types) == 0)
    {
        elem->pc = (elem->pc + data->dep) % MEM_SIZE;
        free(params);
        free(param_types);
        return ;
    }
    if (opc == 0x0C || opc == 0x09 || opc == 0x01 || data->map[elem->pc] == 0x10)
    {
        instr_no_ocp(data, elem, params);
        if (elem_tmp == elem->pc)
            elem->pc = (elem->pc + data->dep) % MEM_SIZE;
        return ;
    }
    instr_w_ocp(data, elem, params, param_types);
    elem->pc = (elem->pc + data->dep) % MEM_SIZE;
    free(params);
    free(param_types);
}
