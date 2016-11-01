/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:08:14 by tbui              #+#    #+#             */
/*   Updated: 2016/11/01 17:21:09 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"


int                 trans_four_bytes(char *transfer_bytes)
{
    unsigned int value;
    int decal; 
    int i;

    i = 0;//index counter for the loop
    decal = 24;
    while (i < DIR_SIZE)
    {
        value |= (transfer_bytes[i] << decal & 0xff);
        decal = decal - 8;
        i++;
    }
    return (value);
}//this function takes four char bytes and puts them into an int using bit operators

char    *get_dir_value_quatre(t_data *data, t_list *elem, int prm_pos) //prm_pos being the position fo the first octet to be extracted out of the parameter
{
	char *four_bytes; //this will be a string, containing the four bytes extracted
	int i; //counter for the the extarction of bytes
	int k; //counter for the loop, as well as the copy destination

	k = 0;
	i = (elem->pc + prm_pos) % MEM_SIZE;
	four_bytes = ft_strnew(5);
	while (k < REG_SIZE)
	{
		four_bytes[k] = data->map[i % MEM_SIZE];
		i++;
		k++;
	}
	return (four_bytes);
}//this function puts four bytes into a string for further conversion into an unsgned int



//called from parameters.c
int 	       	get_dir_value(t_data *data, t_list *elem, int *prm_pos)//prm_pos is the position of the first address byte of the parameter to be searched
{
    int dir_val; //the direct value to be returned
    char *bytes;

    dir_val = 0;
    if (elem->dir_by == 0) //if the direct is supposed to be on the next four bytes
    {


        bytes = get_dir_value_quatre(data, elem, (*prm_pos));
    	dir_val = trans_four_bytes(bytes);
    	(*prm_pos) = (*prm_pos) + 4;
    }
        //code a function which will add the prm_pos onto the pc and then extract the dir out of the next 4 bytes
    else if (elem->dir_by == 1)
    {
		bytes = get_two_bytes(data, elem, (*prm_pos));
		dir_val = trans_two_bytes(bytes);	
		(*prm_pos) = (*prm_pos) + 2;
    }
    return (dir_val);

}//this function gets the direct value, whether it's on four or two bytes
