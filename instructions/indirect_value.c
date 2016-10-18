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
