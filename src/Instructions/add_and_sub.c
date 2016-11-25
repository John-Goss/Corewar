/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:18:48 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/25 19:24:30 by jle-quer         ###   ########.fr       */
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
	while (param_types[i] != 0)
	{
		if (param_types[i] != REG_CODE)
			return ;
		i++;
	}
	store = elem->reg_number[params[0]] + elem->reg_number[params[1]];
	elem->reg_number[params[2]] = store;
	if (elem->carry)
		elem->carry = 0;
	else if (!elem->carry)
		elem->carry = 1;
}

void		apply_sub(t_data *data, t_list *elem, unsigned int *params,
		unsigned int *param_types)
{
	int store;
	int i;

	i = 0;
	store = 0;
	(void)data;
	while (param_types[i] != 0)
	{
		if (param_types[i] != REG_CODE)
			return ;
		i++;
	}
	store = elem->reg_number[params[0]] - elem->reg_number[params[1]];
	elem->reg_number[params[2]] = store;
	if (elem->carry)
		elem->carry = 0;
	else if (!elem->carry)
		elem->carry = 1;
}
