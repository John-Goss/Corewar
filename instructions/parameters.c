/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:08:35 by tbui              #+#    #+#             */
/*   Updated: 2016/11/01 17:06:53 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"
//deteermining the paramater types below

//if the last flag in the instructions is at 0 that means we need to get the direct parameter out of 4 bytes.


//essential question: During the extraciton of the paramters do we also put the addresses realtive to IDX?
//example if there is a direct value to be taken out of the first parameter, do we take pc + 2 or pc + (2 % IDX_MOD) ??

char *conv_dec_to_bin(int n)
{
    char *bin_nbr;
    int remainder;
    int i;
    int k;

    bin_nbr = ft_strnew(9);
    i = 1;
    k = 0;
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

unsigned int     *type_tab_make(char *types_bin, unsigned  int *type_tab)
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
        ty++;
    }
    ft_strdel(&para_bi);
    return (type_tab);
}//this function extracts the parameter types out of the given binary
    //and puts it 


//determining the parameter types above 

int                 two_or_four(t_data *data, t_list *elem)
{
    if (data->map[elem->pc] == 0x02 || data->map[elem->pc] == 0x03 || \
        data->map[elem->pc] == 0x04 || data->map[elem->pc] == 0x05 || \
        data->map[elem->pc] == 0x06 || data->map[elem->pc] == 0x07 || \
        data->map[elem->pc] == 0x08 || data->map[elem->pc] == 0x10 || \
        data->map[elem->pc] == 0x0D || data->map[elem->pc] == 0x01)
        return (0);
    else if (data->map[elem->pc] == 0x09 || data->map[elem->pc] == 0x0A || \
        data->map[elem->pc] == 0x0B || data->map[elem->pc] == 0x0E || \
        data->map[elem->pc] == 0x0F || data->map[elem->pc] == 0x0C)
        return (1);
    return (0); //provisionary
}//this function compares the opc indicator in the list with all the opcs and then looks if the direct parameter is on two or four bytes

unsigned int     *det_types(unsigned int parameter_types)
{
    char			*types_bin;
    unsigned int	*type_tab;

    types_bin = conv_dec_to_bin(parameter_types);
	types_bin = rev_str(types_bin); //figure out if we have to reverse it or not
    if ((!(type_tab = (unsigned int *)malloc(sizeof(unsigned int) * 5))))
        return (NULL);
    type_tab = type_tab_make(types_bin, type_tab);
    return (type_tab);
}//this function makes an int array with the parameter types of the instruction
    //in order!

int                 octet_cod(t_data *data, t_list *elem)
{

    if (data->map[elem->pc] == 0x02 || data->map[elem->pc] == 0x03 ||\
        data->map[elem->pc] == 0x04 || data->map[elem->pc] == 0x05 || \
        data->map[elem->pc] == 0x06 || data->map[elem->pc] == 0x07 || \
        data->map[elem->pc] == 0x08 || data->map[elem->pc] == 0x0A || \
        data->map[elem->pc] == 0x0B || data->map[elem->pc] == 0x0E || \
        data->map[elem->pc] == 0x0D)
        return (2);
    else if (data->map[elem->pc] == 0x0C || data->map[elem->pc] == 0x01 ||\
     data->map[elem->pc] == 0x09 || data->map[elem->pc] == 0x0F || \
     data->map[elem->pc] == 0x10)
        return (1);
    return (0); //this is an error case
}

unsigned int         *get_params(unsigned int *par_types, t_data *data, t_list *elem) //if the ocp is there ONLY!!!
{
    unsigned int *params;
    int i; //counter for the par_types tab
    int k; //counter for the params tab

    k = 0;
    i = octet_cod(data, elem);
    elem->dir_by = 0;
    elem->dir_by = two_or_four(data, elem);//determining whether the direct is on 2 or 4 bytes
    if (!(params = (unsigned int *)malloc(sizeof(int) * 5)))
        return (NULL);
    while (par_types[k] != 0) //this loop checks the param types and fills the param array wtih the corresponding values in order
    {

		if (par_types[k] == REG_CODE)
        {
            params[k] = data->map[(elem->pc + i) % MEM_SIZE]; //getting the register number, the value I still need to get out of the register in the process itself
            i = i + 1;
        }
        else if (par_types[k] == IND_CODE) //this gets either the value the we need to jump to relative to the pc for the indirect, or the reg number
        {
            params[k] = get_ind_value(data, elem, i);
            i = i + 2;
        }
        else if (par_types[k] == DIR_CODE) 
            params[k] = get_dir_value(data, elem, &i);
     //   printf("--->TESTparams:\t%d\n", params[k]);
        printf("--->TESTparams_type:\t%d\n", par_types[k]);
        k++;
    }
    data->dep = i; //
    return (params);//returns to instructions.c
}// this function is self-explanatory, we're getting the parameters guys..

