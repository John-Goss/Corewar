#include "../corewar.h"



void		apply_ld(t_data *data, t_list *elem, int *params, int *param_type)
{
    //value of first parameter into register
    if (param_type[0] == DIR_CODE || param_type[0] == IND_CODE)
	{
        elem->reg_number[params[1]] = params[0];// param[0] is the first parameter
		elem->carry = 1;
	}
    else
    	return ; //I don't think the carry needs to be modified here because in this case the instruction wouldn't have been executed
    //modify carry
    
    //params[1] is the vnumber of the register we need
}
//{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
