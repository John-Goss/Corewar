/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:19:25 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/25 19:25:17 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	apply_and(t_data *data, t_list *elem, unsigned int *params,
			unsigned int *param_type)
{
	int	value_one;
	int	value_two;

	value_one = 0;
	value_two = 0;
	(void)data;
	if (param_type[0] == REG_CODE)
		value_one = elem->reg_number[params[0]];
	else if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
		value_one = params[0];
	if (param_type[1] == REG_CODE)
		value_two = elem->reg_number[params[1]];
	else if (param_type[1] == DIR_CODE || param_type[1] == IND_CODE)
		value_two = params[1];
	elem->reg_number[params[2]] = value_one & value_two;
	if (!elem->carry)
		elem->carry = 1;
	else if (elem->carry)
		elem->carry = 0;
}

void	apply_or(t_data *data, t_list *elem, unsigned int *params,
			unsigned int *param_type)
{
	int value_one;
	int value_two;

	value_one = 0;
	value_two = 0;
	(void)data;
	if (param_type[0] == REG_CODE)
		value_one = elem->reg_number[params[0]];
	else if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
		value_one = params[0];
	if (param_type[1] == REG_CODE)
		value_two = elem->reg_number[params[1]];
	else if (param_type[1] == DIR_CODE || param_type[1] == IND_CODE)
		value_two = params[1];
	elem->reg_number[params[2]] = value_one | value_two;
	if (!elem->carry)
		elem->carry = 1;
	else if (elem->carry)
		elem->carry = 0;
}

void	apply_xor(t_data *data, t_list *elem, unsigned int *params,
			unsigned int *param_type)
{
	int	value_one;
	int	value_two;

	value_one = 0;
	value_two = 0;
	(void)data;
	if (param_type[0] == REG_CODE)
		value_one = elem->reg_number[params[0]];
	else if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
		value_one = params[0];
	if (param_type[1] == REG_CODE)
		value_two = elem->reg_number[params[1]];
	else if (param_type[1] == DIR_CODE || param_type[1] == IND_CODE)
		value_two = params[1];
	elem->reg_number[params[2]] = value_one ^ value_two;
	if (!elem->carry)
		elem->carry = 1;
	else if (elem->carry)
		elem->carry = 0;
}
