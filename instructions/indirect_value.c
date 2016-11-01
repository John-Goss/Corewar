/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:08:01 by tbui              #+#    #+#             */
/*   Updated: 2016/11/01 17:23:39 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

unsigned int                 trans_two_bytes(char *transfer_bytes)
{
    unsigned int value;
    int decal;
    int i;

    i = 0;//index counter for the loop
    decal = 8;
    value = 0;
  //    printf("(--TEST-->%d)\n", value);
    while (i < IND_SIZE)// && transfer_bytes[i] != '\0')
    {
        value |= (transfer_bytes[i] << decal & 0xff);
        decal = decal - 8;
        i++;
    //    printf("(--TEST-->%d)\n", value);
    }
    return (value);
}//this function does the same as trans_four_bytes but with two bytes instead of four... obviously


char                   *get_two_bytes(t_data *data, t_list *elem, int prm_pos) //prm_pos being the position fo the first octet to be extracted out of the parameter

{
    char *two_bytes; //this will be a string, containing the four bytes extracted
    int i; //counter for the the extarction of bytes
    int k; //counter for the loop, as well as the copy destination

    k = 0;
    i = (elem->pc + prm_pos) % MEM_SIZE;
    two_bytes = NULL;
    two_bytes = ft_strnew(5);
    while (k < IND_SIZE)
    {
        two_bytes[k] = data->map[i % MEM_SIZE];
        i++;
        k++;
    }
	return (two_bytes);
}//this function puts four bytes into a string for further conversion into an unsgned int

unsigned int         get_ind_value(t_data *data, t_list *elem, int prm_pos)
{
    unsigned int ind_value;
    char *transfer_bytes;


    ind_value = 0;
    transfer_bytes = get_two_bytes(data, elem, prm_pos); //getting the 2 indirect bytes into a string for transfer, into an int
    ind_value = trans_two_bytes(transfer_bytes); //found in parameters.c
    ind_value = (elem->pc + ind_value) % MEM_SIZE; //I think this is how you modulo everything, but no idea
    //ind_value = data->map[(elem->pc + (add_to_pc % IDX_MOD)) % MEM_SIZE];
    return (ind_value);
}
