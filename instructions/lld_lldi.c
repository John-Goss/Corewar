/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 18:12:49 by tbui              #+#    #+#             */
/*   Updated: 2016/10/20 18:12:51 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


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
