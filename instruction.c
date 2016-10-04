/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instuction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 12:01:01 by lbaudran          #+#    #+#             */
/*   Updated: 2016/09/16 12:27:07 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void		apply_add(t_data *data)
{
	int store;
	int reg_one;
	int reg_two;

	reg_one = data.map[data->begin.pc + 2 % MEM_SIZE];
	reg_two = data.map[data->begin.pc + 3 % MEM_SIZE];
	store = data.map[data->begin.pc + 4 % MEM_SIZE];
	reg_number[store] = reg_number[reg_one] + reg_number[reg_two];
	data->begin.carry = 1;
}

void		apply_sub(t_data *data)
{
	int store;
	int reg_one;
	int reg_two;

	reg_one = (int)data.map[data->begin.pc + 2 % MEM_SIZE];
	reg_two = (int)data.map[data->begin.pc + 3 % MEM_SIZE];
	store = (int)data.map[data->begin.pc + 4 % MEM_SIZE];
	reg_number[store] = reg_number[reg_one] - reg_number[reg_two];
	data->begin.carry = 1;
}//same as add but subtraction
//add & sub functions above


//deteermining the paramater types below
void		det_(int types)
{
	

}
//determining the parameter types above