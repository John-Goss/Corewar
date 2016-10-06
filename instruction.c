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


void        choisir_instru()
{
   
    if (pc == 0x01)
       apply_live(data, elem);
    else if (pc == 0x02)
        //lds
    else if (pc == 0x03)
        //st
    else if (pc == 0x04)
        apply_add(data, elem);
    else if (pc == 0x05)
        apply_sub(data, elem);
    else if (pc == 0x06)
        //and
    else if (pc == 0x07)
        //or
    else if (pc == 0x08)
        //xor
    else if (pc == 0x09)
        //zjmp    
    else if (pc == 0x10)
        //aff
    else if (pc == 0x0A)
        //ldi
    else if (pc == 0x0B)
        //sti
    else if (pc == 0x0C)
        //fork
    else if (pc == 0x0E)
        //lldi
    else if (pc == 0x0F)
        //lfork
    else if (pc == 0x0D)
        //lld
}




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
        return (REG_CODE); //register
    else if (ft_strcmp(para_bi, "10") == 0)
        return (DIR_CODE); //direct
    else if (ft_strcmp(para_bi, "11") == 0)
        return (IND_CODE); //indirect
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
    if ((!(type_tab = (int *)malloc(sizeof(int) * 5))))
        return (NULL);
    type_tab = type_tab_make(types_bin, type_tab);
	return (type_tab);
}//this function makes an int array with the parameter types of the instruction
    //in order!

//determining the parameter types above 


int         get_ind_value(t_data *data, t_list *elem, int val_pos)
{
    int ind_value;
    int add_by; //this plus the pc is the address of the value looked for

    add_by = data->map[(elem->pc + val_pos) % MEM_SIZE];
    ind_value = data->map[(elem->pc + add_by) % MEM_SIZE];
    return (ind_value);
}

int         *get_params(int *par_types, t_data *data, t_list *elem) //if the ocp is there
{
    int *params;
    int i; //counter for the par_types tab

    i = 0
    if (!(params = (int *)malloc(sizeof(int) * 5)))
        return (NULL);
    while (par_types[i] != 0) //this loop check the param types and fills the param array wtih the corresponding values in order
    {
        if (par_types[i] == REG_CODE)
            params[i] = elem->reg_number[data->map[(elem->pc + (i + 2)) % MEM_SIZE]]; //getting the register number
        else if (par_types[i] == DIR_CODE)
            params[i] = data->map[(elem->pc + (i + 2)) % MEM_SIZE];
        else if (par_types[i] == IND_CODE)
            params[i] = get_ind_value(data, elem, i + 2);
        i++;
    }
    return (params);
}

void        instruction_exec(t_data *data, t_list *elem)
{
    int *param_types;
    int *params;
    char opc; //DO NOT CONFUSE WITH OCP!!!

    //THE PC IS ON THE OPC AT THIS POINT
    opc = data->map[(elem->pc) % MEM_SIZE];
    param_types = det_types(data->map[(elem->pc) % MEM_SIZE]);


    if (opc == 0x0C || opc == 0x09 || opc == 0x01)
        elem->ocp_there = 1;


    params = get_params(param_types, data, elem);


}














