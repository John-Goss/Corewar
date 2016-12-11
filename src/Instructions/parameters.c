/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:22:48 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/11 18:22:26 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int				octet_cod_there(t_data *data, t_list *elem)
{
	if (data->map[elem->pc] == 0x02 || data->map[elem->pc] == 0x03 || \
			data->map[elem->pc] == 0x04 || data->map[elem->pc] == 0x05 || \
			data->map[elem->pc] == 0x06 || data->map[elem->pc] == 0x07 || \
			data->map[elem->pc] == 0x08 || data->map[elem->pc] == 0x0A || \
			data->map[elem->pc] == 0x0B || data->map[elem->pc] == 0x0E || \
			data->map[elem->pc] == 0x0D || data->map[elem->pc] == 0x10)
		return (1);
	else if (data->map[elem->pc] == 0x0C || data->map[elem->pc] == 0x01 || \
			data->map[elem->pc] == 0x09 || data->map[elem->pc] == 0x0F)
		return (0);
	return (0);
}

char			*get_par_types_no_ocp(t_data *data, t_list *elem)
{
	if (data->map[elem->pc] == 0x0C)
		return (ft_strdup("10"));
	else if (data->map[elem->pc] == 0x01)
		return (ft_strdup("10"));
	else if (data->map[elem->pc] == 0x09)
		return (ft_strdup("10"));
	else if (data->map[elem->pc] == 0x0F)
		return (ft_strdup("10"));
	else
		return (NULL);
}

/*
** this function makes an int array with the parameter types of the instruction
** in order !
*/

unsigned int	*det_types(t_data *data, t_list *elem,
		unsigned int parameter_types)
{
	char			*types_bin;
	unsigned int	*type_tab;

	type_tab = NULL;
	types_bin = NULL;
	if ((!(type_tab = (unsigned int *)malloc(sizeof(unsigned int) * 5))))
		return (NULL);
	ft_bzero(type_tab, (sizeof(unsigned int)) * 5);
	if (octet_cod_there(data, elem) == 0)
	{
		types_bin = get_par_types_no_ocp(data, elem);
		type_tab = type_tab_make(types_bin, type_tab);
		return (type_tab);
	}
	types_bin = conv_dec_to_bin(parameter_types);
	types_bin = rev_str(types_bin);
	type_tab = type_tab_make(types_bin, type_tab);
	return (type_tab);
}

int				octet_cod(t_data *data, t_list *elem)
{
	if (data->map[elem->pc] == 0x02 || data->map[elem->pc] == 0x03 || \
			data->map[elem->pc] == 0x04 || data->map[elem->pc] == 0x05 || \
			data->map[elem->pc] == 0x06 || data->map[elem->pc] == 0x07 || \
			data->map[elem->pc] == 0x08 || data->map[elem->pc] == 0x0A || \
			data->map[elem->pc] == 0x0B || data->map[elem->pc] == 0x0E || \
			data->map[elem->pc] == 0x0D || data->map[elem->pc] == 0x10)
		return (2);
	else if (data->map[elem->pc] == 0x0C || data->map[elem->pc] == 0x01 || \
			data->map[elem->pc] == 0x09 || data->map[elem->pc] == 0x0F)
		return (1);
	return (0);
}

unsigned int	*get_params(unsigned int *par_types, t_data *data, t_list *elem)
{
	unsigned int	*params;
	int				cpt[2];

	cpt[0] = -1;
	cpt[1] = octet_cod(data, elem);
	params = NULL;
	elem->dir_by = two_or_four(data, elem);
	params = ft_memalloc(20);
	while (par_types[++cpt[0]] != 0)
	{
		if (par_types[cpt[0]] == REG_CODE)
		{
			params[cpt[0]] = (data->map[(elem->pc + cpt[1]) % MEM_SIZE]);
			cpt[1] = cpt[1] + 1;
		}
		else if (par_types[cpt[0]] == IND_CODE)
		{
			params[cpt[0]] = get_ind_value(data, elem, cpt[1]);
			cpt[1] = cpt[1] + 2;
		}
		else if (par_types[cpt[0]] == DIR_CODE)
			params[cpt[0]] = get_dir_value(data, elem, &cpt[1]);
	}
	data->dep = cpt[1];
	return (params);
}
