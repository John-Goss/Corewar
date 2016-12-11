/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:33 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/11 18:41:41 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** param[0] is the first parameter.
*/

void	apply_lld(t_data *data, t_list *elem, unsigned int *param_types,
		unsigned int *params)
{
	int	i;

	i = 0;
	if (param_types[0] == DIR_CODE)
		i = (int)params[0];
	else if (param_types[0] == IND_CODE)
		i = (short)recup_ind(data, params[0], elem->pc);
	else if (param_types[0] == REG_CODE)
		i = elem->reg_number[params[0]];
	elem->reg_number[params[1]] = i;
	if (elem->reg_number[params[1]] == 0)
		elem->carry = 1;
	else
		elem->carry = 0;
}

void	apply_lldi(t_data *data, t_list *elem, unsigned int *param_types,
		unsigned int *params)
{
	unsigned int	value_one;
	unsigned int	value_two;
	unsigned int	store;

	store = 0;
	value_one = 0;
	value_two = 0;
	if (param_types[0] == DIR_CODE)
		value_one = (short)params[0];
	else if (param_types[0] == IND_CODE)
		value_one = recup_ind(data, (short)params[0], elem->pc);
	else if (param_types[0] == REG_CODE)
		value_one = elem->reg_number[params[0]];
	if (param_types[1] == DIR_CODE)
		value_two = (short)params[1];
	else if (param_types[1] == REG_CODE)
		value_two = elem->reg_number[params[1]];
	store = value_one + value_two;
	elem->reg_number[params[2]] = store;
	if (store == 0)
		elem->carry = 1;
	else
		elem->carry = 0;
}
