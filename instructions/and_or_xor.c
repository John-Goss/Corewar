/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 12:07:06 by tbui              #+#    #+#             */
/*   Updated: 2016/11/11 17:18:13 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void        apply_and(t_data *data,t_list *elem, unsigned int *params, unsigned int *param_type)
{
    int value_one; //param values
    int value_two;


    if (param_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
        value_one = params[0];
    if (param_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (param_type[1] == DIR_CODE || param_type[1] == IND_CODE)
        value_two = params[1];
//		printf("TEST 0 %d\n", params[0]);
//		printf("TEST 1 %d\n", params[1]);
//		printf("TEST 2 %d\n", params[2]);
    elem->reg_number[params[2]] = value_one & value_two;//so now we got the two values which we need to stock
	if (!elem->carry)
		elem->carry = 1;
	else if (elem->carry)
		elem->carry = 0;
}//the bit operation & is executed on the first two and then stored at the third which is a register


void        apply_or(t_data *data,t_list *elem, unsigned int *params, unsigned int *param_type)
{
    int value_one; //param values
    int value_two;

    if (param_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
        value_one = params[0];
    if (param_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (param_type[1] == DIR_CODE || param_type[1] == IND_CODE)
        value_two = params[1];
    elem->reg_number[params[2]] = value_one | value_two;//so now we got the two values which we need to stock
	if (!elem->carry)
		elem->carry = 1;
	else if (elem->carry)
		elem->carry = 0;
}//the bit operation | is executed on the first two and then stored at the third which is a register


void        apply_xor(t_data *data,t_list *elem, unsigned int *params, unsigned int *param_type)
{
    int value_one; //param values
    int value_two;

    if (param_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
        value_one = params[0];
    if (param_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (param_type[1] == DIR_CODE || param_type[1] == IND_CODE)
        value_two = params[1];
    elem->reg_number[params[2]] = value_one ^ value_two;//so now we got the two values which we need to stock
	if (!elem->carry)
		elem->carry = 1;
	else if (elem->carry)
		elem->carry = 0;
}//the bit operation ^ is executed on the first two and then stored at the third which is a register

