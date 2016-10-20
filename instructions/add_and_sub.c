/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:43:20 by tbui              #+#    #+#             */
/*   Updated: 2016/10/20 19:43:21 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		apply_add(t_data *data, t_list *elem, int *params, int *param_types)
{
	int store;
	int i;

	i = 0;
	store = 0;
	while (param_types[i] != 0)//this loop verifies if all the param types are truly registers
	{
		if (param_types[i] != REG_CODE)
		{
			ft_putstr("ERROR in add instruction, param types are invalid\n");//this is just for testing
			return ; //not sure if I need this kind of error handing
		}
		i++;
	}
	store = elem->reg_number[params[0]] + elem->reg_number[params[1]];
	elem->reg_number[params[2]] = store;
	elem->carry = 1;
}

void		apply_sub(t_data *data, t_list *elem, int *params, int *param_types)
{
	int store;
	int i;

	i = 0;
	store = 0;
	while (param_types[i] != 0)//this loop verifies if all the param types are truly registers
	{
		if (param_types[i] != REG_CODE)
		{
			ft_putstr("ERROR in add instruction, param types are invalid\n");//this is just for testing
			return ; //not sure if I need this kind of error handing
		}
		i++;
	}
	store = elem->reg_number[params[0]] - elem->reg_number[params[1]];
	elem->reg_number[params[2]] = store;
	elem->carry = 1;
}
