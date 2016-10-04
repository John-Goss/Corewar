/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instuction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 12:01:01 by lbaudran          #+#    #+#             */
/*   Updated: 2016/10/04 17:57:24 by lbaudran         ###   ########.fr       */
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

void		apply_live(t_data *data, t_list *elem)
{
	t_desc	*desc;
	int		nb_champ;

	nb_champ = data->map[(elem->pc + 1) % MEM_SIZE];
	elem->pc = (elem->pc + 2) % MEM_SIZE;
	data->live_cpt++;
	while (desc)
	{
		if (nb_champ == desc->nb_champ)
			data->last_live_nb_champ = nb_champ;
		desc = desc->next;
	}
}

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
}//this gives me a string with a converted reversed binary

char        *rev_str(char *string)
{
    int i;
    int k;
    char *rev_str;

    i = 0;
    k = 0;
    while (string[k] != '\0')
        k++;
    k--;
    rev_str = ft_strnew(k);
    while (k >= 0)
    {
        rev_str[i] = string[k];
        i++;
        k--;
    }
    return (rev_str);
}//this function reverses my reversed binary so I can 
    //have the proper binary

int             extr_typ_from_bin(char *para_bi)
{
    if (ft_strcmp(para_bi, "01") == 0)
        return (1); //register
    else if (ft_strcmp(para_bi, "10") == 0)
        return (2); //direct
    else if (ft_strcmp(para_bi, "11") == 0)
        return (3); //indirect
    else
        return (0);
}// this function returns a value which will determine the
//parameter type

int     *type_tab_make(char *types_bin, int *type_tab)
{
    int i; //counter for binary
    int k;  //counter for pairs of bits
    char *para_bi;//two bits which we will interpret as param types
    int ty; //counter index for param types array

    i = 0;
    ty = 0;
    para_bi = ft_strnew(2);
    while (types_bin[i] != '\0')
    {
        k = 0;
        while (k <= 1)
        {
            para_bi[k] = types_bin[i];
            i++;
            k++;
        }
        type_tab[ty] = extr_typ_from_bin(para_bi);
        printf("\n\n(%d)\n", type_tab[ty]);
        ty++;
    }
    ft_strdel(&para_bi);
    return (type_tab);
}//this function extracts the parameter types out of the given binary
    //and puts it 

int     *det_types(unsigned int parameter_types)
{
	unsigned int determine;
	int types;
	char *types_bin;
    int *type_tab;

	determine = 255;
	types = parameter_types & determine;
	types_bin = conv_dec_to_bin(types);
    types_bin = rev_str(types_bin);
    if ((!(type_tab = (int *)malloc(sizeof(int) * 4))))
        return (NULL);
    type_tab = type_tab_make(types_bin, type_tab);
	return (type_tab);
}//this function makes an int array with the parameter types of the instruction
    //in order!

//determining the parameter types above 




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
