/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:23:03 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/07 18:46:42 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

/*
** this gives me a string with a converted reversed binary.
*/

char			*conv_dec_to_bin(int n)
{
	char	*bin_nbr;
	int		remainder;
	int		i;
	int		k;

	bin_nbr = ft_strnew(9);
	i = 1;
	k = 0;
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
}

/*
** this function reverses my reversed binary so I can have the proper binary.
*/

char			*rev_str(char *string)
{
	int		i;
	int		k;
	char	*rev_str;

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
}

/*
** this function returns a value which will determine the parameter type.
*/

int				extr_typ_from_bin(char *para_bi)
{
	if (ft_strcmp(para_bi, "01") == 0)
		return (REG_CODE);
	else if (ft_strcmp(para_bi, "10") == 0)
		return (DIR_CODE);
	else if (ft_strcmp(para_bi, "11") == 0)
		return (IND_CODE);
	else
		return (0);
}

/*
** this function extracts the parameter types out of the given binary
** and puts it.
*/

unsigned int	*type_tab_make(char *types_bin, unsigned int *type_tab)
{
	int		i;
	int		k;
	char	*para_bi;
	int		ty;

	i = 0;
	ty = 0;
	para_bi = ft_strnew(2);
	while (types_bin && types_bin[i] && i < 6)
	{
		k = 0;
		while (k <= 1)
		{
			para_bi[k] = types_bin[i];
			i++;
			k++;
		}
		type_tab[ty] = extr_typ_from_bin(para_bi);
		ty++;
	}
	free(para_bi);
	return (type_tab);
}

/*
** this function compares the opc indicator in the list with all the opcs and
** then looks if the direct parameter is on two or four bytes.
*/

int				two_or_four(t_data *data, t_list *elem)
{
	if (data->map[elem->pc] == 0x02 || data->map[elem->pc] == 0x03 || \
			data->map[elem->pc] == 0x04 || data->map[elem->pc] == 0x05 || \
			data->map[elem->pc] == 0x06 || data->map[elem->pc] == 0x07 || \
			data->map[elem->pc] == 0x08 || data->map[elem->pc] == 0x10 || \
			data->map[elem->pc] == 0x0D || data->map[elem->pc] == 0x01)
		return (0);
	else if (data->map[elem->pc] == 0x09 || data->map[elem->pc] == 0x0A || \
			data->map[elem->pc] == 0x0B || data->map[elem->pc] == 0x0E || \
			data->map[elem->pc] == 0x0F || data->map[elem->pc] == 0x0C)
		return (1);
	return (0);
}
