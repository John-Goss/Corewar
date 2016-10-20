#include "corewar.h"

void        put_in_bytes(t_data *data,t_list *elem, int address, int params)//move this function to the top of the instructions filee
{
	char byte_array[4];

	byte_array[0] = (params >> 24) & 0xFF;
	byte_array[1] = (params >> 16) & 0xFF;
	byte_array[2] = (params >> 8) & 0xFF;
	byte_array[3] = params & 0xFF;

	data->map[elem->pc + address] = byte_array[0];
	data->map[elem->pc + address + 1] = byte_array[1];
	data->map[elem->pc + address + 2] = byte_array[2];
	data->map[elem->pc + address + 3] = byte_array[3];
}

void		apply_sti(t_data *data, t_list *elem, int *param_types, int *params)
{
    int value_one;
    int value_two;
    int address;

    address = 0;
    if (param_types[1] == DIR_CODE || param_types[1] == IND_CODE)
        value_one = params[1];
    else if (param_types[0] == REG_CODE)
        value_one = elem->reg_number[params[1]]; 
    if (param_types[2] == DIR_CODE)
        value_two = params[2];
    else if (param_types[2] == REG_CODE)
        value_two = elem->reg_number[params[2]];
    address = value_one + value_two;
    put_in_bytes(data, elem, address, elem->reg_number[params[0]]);//this function puts the desired value onto the required number of bytes in the memory

    //getting the value at the address which we've determined by combining the values of the last two parameters
        //then putting the value we found at that address into the register, given to us in the first parameter
}//{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
//     "store index", 1, 1},

                
