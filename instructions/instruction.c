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

//Finish coding apply_aff
//find out how to direct the process into the given instruction
//test and refactor EVERYTHING!
//refactor all instructions
//figure how the carry modifications work, and what it means to "modify the carry" do we always put it to 1?

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
        apply_add(data, elem, params, param_types);
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

//takes two paramters of which the third will always be register


void		apply_zjmp(t_data *data, t_list *elem, int *params)
{
    if (elem->carry == 1)
            elem->pc = (elem->pc + (params[0] % IDX_MOD)) % MEM_SIZE;
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
