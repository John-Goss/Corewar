/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 12:01:01 by lbaudran          #+#    #+#             */
/*   Updated: 2016/10/07 14:03:46 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//Finish coding all the single instructions
//learn how to get a direct parameter out of either 4 or 2 bytes, presumably with bit operators
//find out how to direct the process into the given instruction
//test and refactor EVERYTHING!

void        instr_no_ocp(t_data *data, t_list *elem)
{
    if (pc == 0x0C)  
       //fork
    else if (pc == 0x01)
       apply_live(data, elem);   
    else if (pc == 0x09)
        //zjmp    
}

void         instr_w_ocp(t_data *data, t_list *elem, int *params, int *param_types);
{
    else if (pc == 0x02)
        apply_ld(data, elem, params);
    else if (pc == 0x03)
        apply_st(data, elem, params, param_types);
    else if (pc == 0x04)
        apply_add(data, elem);
    else if (pc == 0x05)
        apply_sub(data, elem);
    else if (pc == 0x06)
        apply_and(data, elem, params, param_types);
    else if (pc == 0x07)
        apply_or(data, elem, params, param_types);
    else if (pc == 0x08)
        apply_xor(data, elem, params, param_types);
    else if (pc == 0x10)
        //aff
    else if (pc == 0x0A)
        //ldi
    else if (pc == 0x0B)
        //sti
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
	//elem->pc = ((elem->pc + (4 % IDX_MOD)) % MEM_SIZE);
}

void		apply_sub(t_data *data, t_list *elem)
{
	int store;
	int reg_one;
	int reg_two;
    reg_one = data->map[(elem->pc + 2) % MEM_SIZE];
    reg_two = data->map[(elem->pc + 3) % MEM_SIZE];
    store = data->map[(elem->pc + 4) % MEM_SIZE];
	elem->reg_number[store] = elem->reg_number[reg_one] - elem->reg_number[reg_two];
	elem->carry = 1;
	//elem->pc = (elem->pc + 4) % MEM_SIZE;
}//same as add but subtraction
//add & sub functions above

void		apply_live(t_data *data, t_list *elem)
{
	t_desc	*desc;
	int		nb_champ;

	nb_champ = data->map[(elem->pc + (1 % IDX_MOD)) % MEM_SIZE];
	elem->pc = (elem->pc + 2) % MEM_SIZE;
	data->live_cpt++;
	while (desc)
	{
		if (nb_champ == desc->nb_champ)
			data->last_live_nb_champ = nb_champ;
		desc = desc->next;
	}
}

void		apply_ld(t_data *data, t_list *elem, int *params, int *param_types)
{
    //value of first parameter into register
    if (param_type[0] == DIR_CODE)
        elem->reg_number[params[1]] = params[0];// param[0] is the first parameter
    else if (param_type[0] == DIR_CODE)
        elem->reg_number[params[1]] = get_ind_value_idxd(params[0]);
    else if (param_types[0] == REG_CODE)
        elem->reg_number[params[1]] = elem->reg_number[params[0]];
    //params[1] is the vnumber of the register we need
}

void		apply_st(t_data *data, t_list *elem, int *params, int *param_types)
{

    if (param_types[1] == IND_CODE)//go to the address (PC plus value) and store first value
        data->map[params[1]] =  elem->reg_number[params[0]]; //value to copy into the other place
    else if (param_types[1] == REG_CODE)//put the value to be copied into the register
        elem->reg_number[params[1]] = elem->reg_number[params[0]]; //value to copy into the other place
}//this takes the value of a register and STORES it at either an address or another register


//takes two paramters of which the third will always be register
void		apply_and(t_data *data,t_list *elem, int *param, int *param_types)
{
    unsigned int value_one; //param values
    unsigned int value_two;

    if (params_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (params_type[0] == DIR_CODE)
        value_one = params[0];
    else if (params_type[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    if (params_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (params_type[1] == DIR_CODE)
        value_two = params[1];
    else if (params_type[1] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    elem->reg_number[params[2]] = value_one & value_two;//so now we got the two values which we need to stock
}//the bit operation & is executed on the first two and then stored at the third which is a register

void		apply_or(t_data *data, t_list *elem)
{
    unsigned int value_one; //param values
    unsigned int value_two;

    if (params_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (params_type[0] == DIR_CODE)
        value_one = params[0];
    else if (params_type[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    if (params_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (params_type[1] == DIR_CODE)
        value_two = params[1];
    else if (params_type[1] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    elem->reg_number[params[2]] = value_one | value_two;
}

void		apply_xor(t_data *data, t_list *elem)
{
    unsigned int value_one; //param values
    unsigned int value_two;

    if (params_type[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    else if (params_type[0] == DIR_CODE)
        value_one = params[0];
    else if (params_type[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    if (params_type[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    else if (params_type[1] == DIR_CODE)
        value_two = params[1];
    else if (params_type[1] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    elem->reg_number[params[2]] = value_one ^ value_two;


}

void		apply_zjmp(t_data *data, t_list *elem, int *params)
{
    if (elem->carry == 1)
            elem->pc = (elem->pc + (params[0] % IDX_MOD)) % MEM_SIZE;
}

void		apply_ldi(t_data *data, t_list *elem, int *param_types, int *params)
{
    int value_one;
    int value_two;
    int store; //value to store into the given register

    if (param_types[0] == DIR_CODE)
        value_one = params[0];
    else if (param_types[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    else if (param_types[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    if (param_types[1] == DIR_CODE)
        value_two = params[1]
    else if (param_types[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    store = get_ind_value_idxd(value_one + value_two);
    elem->reg_number[params[2]] = store;

}//{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
//        "load index", 1, 1},

void		apply_sti(t_data *data, t_list *elem, int *param_types, int *params)
{
    int value_one;
    int value_two;

    if (param_types[1] == DIR_CODE)
        value_one = params[1];
    else if (param_types[1] == IND_CODE)
        value_one = get_ind_value_idxd(params[1]);
    else if (param_types[0] == REG_CODE)
        value_one = elem->reg_number[params[1]]; //determining the first value which we will use as the an index
    if (param_types[2] == DIR_CODE)
        value_two = params[2];
    else if (param_types[2] == REG_CODE)
        value_two = elem->reg_number[params[2]];
    elem->reg_number[params[0]] = get_ind_value_idxd(value_one + value_two); //getting the value at the address which we've determined by combining the values of the last two parameters
        //then putting the value we found at that address into the register, given to us in the first parameter
}//{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
//     "store index", 1, 1},

                

void		apply_lld(t_data *data, t_list *elem) //addresses not relative to IDX
{
      if (param_type[0] == DIR_CODE)
        elem->reg_number[params[1]] = params[0];// param[0] is the first parameter
    else if (param_type[0] == IND_CODE)
        elem->reg_number[params[1]] = get_ind_value(params[0]);
    else if (param_types[0] == REG_CODE)
        elem->reg_number[params[1]] = elem->reg_number[params[0]];
}

void		apply_lldi(t_data *data, t_list *elem) //addresses not relative to IDX
{

    int value_one;
    int value_two;
    int store; //value to store into the given register

    if (param_types[0] == DIR_CODE)
        value_one = params[0];
    else if (param_types[0] == IND_CODE)
        value_one = get_ind_value_idxd(params[0]);
    else if (param_types[0] == REG_CODE)
        value_one = elem->reg_number[params[0]];
    if (param_types[1] == DIR_CODE)
        value_two = params[1]
    else if (param_types[1] == REG_CODE)
        value_two = elem->reg_number[params[1]];
    store = get_ind_value_idxd(value_one + value_two);
    elem->reg_number[params[2]] = store;
    //figure out carry modification
}

//void		apply_lfork(t_data *data, t_list *elem) //addresses not relative to IDX!
//{
//  //Again... figure out how to split a process
//}
//
//void		apply_aff(t_data *data, t_list *elem)
//{
// //IDK what the fuck this means
//}
//

//void      apply_fork(t_data *data, t_list *elem)
//{
// //figure out how to split a process
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

int         get_ind_value_idxd(t_data *data, t_list *elem, int add_to_pc)
{
    int ind_value;

    ind_value = data->map[(elem->pc + (add_to_pc % IDX_MOD)) % MEM_SIZE]; //the value of the indirect value at its address
    return (ind_value);
}// function to get the indirect value's ADDRESSS into the params array


int         get_ind_value(t_data *data, t_list *elem, int add_to_pc)
{
    int ind_value;
    int ind_address;

    ind_address = elem->pc + add_to_pc; //adding the value found in the parameter with the pc, giving us the address of the indirect value
    ind_value = data->map[ind_address % MEM_SIZE]; //getting the value from the memory
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
        if (par_types[i] == REG_CODE || par_types[i] == IND_CODE) //this gets either the value the we need to jump to relative to the pc for the indirect, or the reg number
            params[i] = data->map[(elem->pc + (i + 2)) % MEM_SIZE]; //getting the register number
        else if (par_types[i] == DIR_CODE)
            params[i] = //learn how to get parameters from several bytes

        i++;
    }
    return (params);
}// this function is self-explanatory, we're getting the parameters guys..

void        instruction_exec(t_data *data, t_list *elem)
{
    int *param_types;
    int *params;
    char opc; //DO NOT CONFUSE WITH OCP!!!

    //THE PC IS ON THE OPC AT THIS POINT
    opc = data->map[(elem->pc) % MEM_SIZE];
    param_types = det_types(data->map[(elem->pc) % MEM_SIZE]);
    params = get_params(param_types, data, elem);
    if (opc == 0x0C || opc == 0x09 || opc == 0x01)
    {
        instr_no_ocp(data, elem);
        return ; //free all the shit first dude
    }
    instr_w_ocp(data, elem, params, param_types);        
}


 //if the last flag in the instructions is at 0 that means we need to get the direct parameter out of 4 bytes.


//essential question: During the extraciton of the paramters do we also put the addresses realtive to IDX?
//example if there is a direct value to be taken out of the first parameter, do we take pc + 2 or pc + (2 % IDX_MOD) ??


