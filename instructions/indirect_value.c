/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:08:01 by tbui              #+#    #+#             */
/*   Updated: 2016/10/18 18:08:05 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char                   *get_two_bytes(t_data *data, t_list *elem, int prm_pos) //prm_pos being the position fo the first octet to be extracted out of the parameter

{
    char *two_bytes; //this will be a string, containing the four bytes extracted
    int i; //counter for the the extarction of bytes
    int k; //counter for the loop, as well as the copy destination

    k = 0;
    i = (elem->pc + prm_pos) % MEM_SIZE;
    four_bytes = ft_strnew(5);
    while (k < IND_SIZE)
    {
        four_bytes[k] = data->map[i % MEM_SIZE];
        i++;
        k++;
    }
    return (two_bytes);
}//this function puts four bytes into a string for further conversion into an unsgned int


unsigned int         get_ind_value_idxd(t_data *data, t_list *elem)
{
    unsigned int ind_value;
    char *transfer_bytes;

    ind_value = 0;
    transfer_bytes = get_two_bytes(data, elem); //getting the 2 indirect bytes into a string for transfer, into an int
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
    transfer_bytes = get_two_bytes(data, elem); //getting the 2 indirect bytes into a string for transfer, into an int
    ind_value = trans_two_bytes(transfer_bytes);
    ind_value = (elem->pc + ind_value) % MEM_SIZE; //I think this is how you modulo everything, but no idea
    //ind_value = data->map[(elem->pc + (add_to_pc % IDX_MOD)) % MEM_SIZE];
    return (ind_value);
}
