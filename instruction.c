/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instuction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 12:01:01 by lbaudran          #+#    #+#             */
/*   Updated: 2016/10/04 17:07:52 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		apply_add(t_data *data, t_list *elem)
{
	int store;
	int reg_one;
	int reg_two;

	reg_one = data->map[(elem->pc + 2) % MEM_SIZE];
	reg_two = data->map[(elem->pc + 3) % MEM_SIZE];
	store = data->map[(elem->pc + 4) % MEM_SIZE];
	elem->reg_number[store] = elem->reg_number[reg_one] + elem->reg_number[reg_two];
	elem->carry = 1;
	elem->pc = (elem->pc + 4) % MEM_SIZE;
}

void		apply_sub(t_data *data, t_list *elem)
{
	int store;
	int reg_one;
	int reg_two;

	reg_one = (int)data->map[(elem->pc + 2) % MEM_SIZE];
	reg_two = (int)data->map[(elem->pc + 3) % MEM_SIZE];
	store = (int)data->map[(elem->pc + 4) % MEM_SIZE];
	elem->reg_number[store] = elem->reg_number[reg_one] - elem->reg_number[reg_two];
	elem->carry = 1;
	elem->pc = (elem->pc + 4) % MEM_SIZE;
}//same as add but subtraction
//add & sub functions above

//deteermining the paramater types below


char *conv_dec_to_bin(int n)
{
    char *bin_nbr;
    int remainder;
    int i;
    int k;

    i = 1;
    k = 0;
    bin_nbr = ft_strnew(9);
    while (n != 0)
    {
        remainder = n % 2;
        n /= 2;

        if (remainder == 0)
        	bin_nbr[k] = '0';
        else if (remainder == 1)
        	bin_nbr[k] = '1';
        i *= 10;
        k++;
    }
  	while (k < 8)
 	{
 		bin_nbr[k] = '0';
   		k++;
 	}
    return (bin_nbr);
}

char 	*det_types(unsigned int parameter_types)
{
	unsigned int determine;
	int types;
	char *types_bin;

	determine = 255;
	types = parameter_types & determine;
	types_bin = conv_dec_to_bin(types);
	return (types_bin);
}

//determining the parameter types above





//void		apply_live(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_ld(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_st(t_data *data, t_list *elem)
//{
//
//}
//
//
//void		apply_and(t_data *data,t_list *elem)
//{
//
//}
//
//void		apply_or(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_xor(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_zjmp(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_ldi(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_sti(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_fork(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_lld(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_lldi(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_lfork(t_data *data, t_list *elem)
//{
//
//}
//
//void		apply_aff(t_data *data, t_list *elem)
//{
//
//}
//
