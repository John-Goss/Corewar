#include "corewar.h"
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
	int determine;
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

unsigned int                 trans_two_bytes(char *transfer_bytes)
{
    unsigned int value;
    int decal; 
    int i;

    i = 0;//index counter for the loop
    decal = 24;
    while (i < IND_SIZE && transfer_bytes[i] != '\0')
    {
        value |= (transfer_bytes[i] << decal);
        decal = decal - 8;
        i++;
    }
    return (value);
}//this function does the same as trans_four_bytes but with two bytes instead of four... obviously

unsigned int                 trans_four_bytes(char *transfer_bytes)
{
    unsigned int value;
    int decal; 
    int i;

    i = 0;//index counter for the loop
    decal = 24;
    while (i < DIR_SIZE && transfer_bytes[i] != '\0')
    {
        value |= (transfer_bytes[i] << decal);
        decal = decal - 8;
        i++;
    }
    return (value);
}//this function takes four char bytes and puts them into an int using bit operators


char               *get_bytes()
{



}//this function puts the parameter bytes into a string for byte transfer later on

unsigned int         get_ind_value_idxd(t_data *data, t_list *elem)
{
    unsigned int ind_value;
    char *transfer_bytes;

    ind_value = 0;
    transfer_bytes = get_bytes(data, elem); //getting the 2 indirect bytes into a string for transfer, into an int
    ind_value = trans_two_bytes(transfer_bytes);
    ind_value = (elem->pc + (ind_value % IDX_MOD)) % MEM_SIZE; //I think this is how you modulo everything, but no idea
    //ind_value = data->map[(elem->pc + (add_to_pc % IDX_MOD)) % MEM_SIZE];
    return (ind_value);
}

unsigned int         get_ind_value(t_data *data, t_list *elem)
{
    unsigned int ind_value;
    char *transfer_bytes;

    ind_value = 0;
    transfer_bytes = get_bytes(data, elem); //getting the 2 indirect bytes into a string for transfer, into an int
    ind_value = trans_two_bytes(transfer_bytes);
    ind_value = (elem->pc + ind_value) % MEM_SIZE; //I think this is how you modulo everything, but no idea
    //ind_value = data->map[(elem->pc + (add_to_pc % IDX_MOD)) % MEM_SIZE];
    return (ind_value);
}


int                 two_or_four(t_data *data, t_list *elem)
{
    if (data->map[elem->pc] == 0x02)
        //ld
    else if (pc == 0x03)
        //apply_st(data, elem, params, param_types);
    else if (pc == 0x04)
        //apply_add(data, elem);
    else if (pc == 0x05)
        //apply_sub(data, elem);
    else if (pc == 0x06)
        //apply_and(data, elem, params, param_types);
    else if (pc == 0x07)
        //apply_or(data, elem, params, param_types);
    else if (pc == 0x08)
        //apply_xor(data, elem, params, param_types);
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
    else if (pc == 0x0C)  
       //fork
    else if (pc == 0x01)
       //apply_live(data, elem);   
    else if (pc == 0x09)
        //zjmp    0


    //this function compares the opc indicator in the list with all the opcs and then looks if the direct parameter is on two or four bytes

}


unsigned int         get_dir_value(t_data *data, t_list *elem, int prm_pos)//prm_pos is the position of the first address byte of the parameter to be searched
{
    



}//this function gets the direct value, whether it's on four or two bytes

unsigned int         *get_params(int *par_types, t_data *data, t_list *elem) //if the ocp is there ONLY!!!
{
    unsigned int *params;
    int i; //counter for the par_types tab
    int k;
    int dir;

    k = 0;
    i = 2;
    elem->dir_by = two_or_four();//determining whether the direct is on 2 or 4 bytes
    if (!(params = (unsigned int *)malloc(sizeof(int) * 5)))
        return (NULL);
    while (par_types[k] != 0) //this loop check the param types and fills the param array wtih the corresponding values in order
    {
        if (par_types[k] == REG_CODE)
        {
            params[k] = data->map[(elem->pc + i) % MEM_SIZE]; //getting the register number, the value I still need to get out of the register in the process itself
            i = i + 1;
        }
        else if (par_types[k] == IND_CODE) //this gets either the value the we need to jump to relative to the pc for the indirect, or the reg number
        {
            params[k] = get_ind_value(data, elem);
            i = i + 2;
        }
        else if (par_types[k] == DIR_CODE && dir == 0) //this only handles the case of the direct parameter being held in 4 bytes
        {
            params[k] = get_dir_value(data, elem, i);//learn how to get parameters from several bytes
            i = i + 4;
        }
        k++;
    }
    return (params);
}// this function is self-explanatory, we're getting the parameters guys..

void        instruction_exec(t_data *data, t_list *elem)
{
    int *param_types;
    unsigned int *params;
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
