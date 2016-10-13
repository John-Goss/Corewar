#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define IND_SIZE            2
#define REG_SIZE            4
#define DIR_SIZE            REG_SIZE

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
            params[i] = data->map[(elem->pc + (i + 2)) % MEM_SIZE]; //getting the register number, the value I still need to get out of the register in the process itself
        else if (par_types[i] == IND_CODE) //this gets either the value the we need to jump to relative to the pc for the indirect, or the reg number
            params[i] = get_ind_value(data, elem);
        else if (par_types[i] == DIR_CODE)
            params[i] = get_dir_value(data, elem);//learn how to get parameters from several bytes

        i++;
    }
    return (params);
}// this function is self-explanatory, we're getting the parameters guys..


int                 trans_two_bytes(char *transfer_bytes, int recup)
{
    int i; //counter for the loop
    int value;
    int decal;

    i = 0;
    decal = 16;
    while (i < IND_SIZE)
    {
        byte = data->map[elem->pc];
        value |= byte << decal;
        decal = decal - 8;
        i++;
    }
    return (value);
}

int                 trans_four_bytes(char *transfer_bytes, int recup)
{
    int i; //counter for the loop
    int value;
    int decal;

    i = 0;
    decal = 24;
    while (i < DIR_SIZE)
    {
        byte = data->map[elem->pc];
        value |= byte << decal;
        decal = decal - 8;
        i++;
    }
    return (value);
}

int                main(int argc, char **argv)
{
	int   four_bytes;
    char *transfer_bytes;

    four_bytes = 0;
	if (argc != 2)
		return (0);

	four_bytes = argv[1];
    four_bytes = trans_four_bytes(transfer_bytes);
	return (0);
}