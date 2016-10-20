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
