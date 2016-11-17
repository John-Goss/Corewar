/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:43:20 by tbui              #+#    #+#             */
/*   Updated: 2016/11/17 17:47:12 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		apply_add(t_data *data, t_list *elem, unsigned int *params, unsigned int *param_types)
{
	int store;
	int i;

	i = 0;
	store = 0;
	while (param_types[i] != 0)//this loop verifies if all the param types are truly registers
	{
		if (param_types[i] != REG_CODE)
			return ; //not sure if I need this kind of error handing
		i++;
	}
	store = elem->reg_number[params[0]] + elem->reg_number[params[1]];
	elem->reg_number[params[2]] = store;
	if (elem->carry)
		elem->carry = 0;
	else if (!elem->carry)
		elem->carry = 1;
}

void		apply_sub(t_data *data, t_list *elem, unsigned int *params, unsigned int *param_types)
{
	int store;
	int i;

	i = 0;
	store = 0;
	while (param_types[i] != 0)//this loop verifies if all the param types are truly registers
	{
		if (param_types[i] != REG_CODE)
			return ; //not sure if I need this kind of error handing
		i++;
	}
	store = elem->reg_number[params[0]] - elem->reg_number[params[1]];
	elem->reg_number[params[2]] = store;
	if (elem->carry)
		elem->carry = 0;
	else if (!elem->carry)
		elem->carry = 1;
}
