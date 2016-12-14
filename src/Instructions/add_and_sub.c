/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:18:48 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/14 16:27:52 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		apply_add(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_types)
{
	int store;
	int i;

	i = 0;
	store = 0;
	(void)data;
	if (param_types[0] != REG_CODE || param_types[1] != REG_CODE ||
			param_types[2] != REG_CODE || params[0] > 15 ||
			params[1] > 15 || params[2] > 15)
		return ;
	while (param_types[i] != 0)
	{
		if (param_types[i] != REG_CODE)
			return ;
		i++;
	}
	store = elem->reg_number[params[0]] + elem->reg_number[params[1]];
	if (store == 0)
		elem->carry = 1;
	else
		elem->carry = 0;
	elem->reg_number[params[2]] = store;
}

void		apply_sub(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_types)
{
	int store;
	int i;

	i = 0;
	store = 0;
	(void)data;
	if (param_types[0] != REG_CODE || param_types[1] != REG_CODE ||
			param_types[2] != REG_CODE || params[0] > 15 ||
			params[1] > 15 || params[2] > 15)
		return ;
	while (param_types[i] != 0)
	{
		if (param_types[i] != REG_CODE)
			return ;
		i++;
	}
	store = elem->reg_number[params[0]] - elem->reg_number[params[1]];
	if (store == 0)
		elem->carry = 1;
	else
		elem->carry = 0;
	elem->reg_number[params[2]] = store;
}
