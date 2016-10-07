/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 16:27:09 by jle-quer          #+#    #+#             */
/*   Updated: 2016/10/05 17:32:20 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
/*
void		init_pt_tab(void (**tab)(t_data *data, t_list *elem))
{
	tab[1] = &apply_live;
	tab[2] = &apply_ld;
	tab[3] = &apply_st;
	tab[4] = &apply_add;
	tab[5] = &apply_sub;
	tab[6] = &apply_and;
	tab[7] = &apply_or;
	tab[8] = &apply_xor;
	tab[9] = &apply_zjmp;
	tab[10] = &apply_ldi;
	tab[11] = &apply_sti;
	tab[12] = &apply_fork;
	tab[13] = &apply_lld;
	tab[14] = &apply_lldi;
	tab[15] = &apply_lfork;
	tab[16] = &apply_aff;
}
*/
t_desc		*create_desc2(t_desc **desc, int nb, int *used_nb)
{
	t_desc	*elem;
	elem = *desc;

	while (elem)
		elem = elem->next;
	if (!(elem = (t_desc *)malloc(sizeof(t_desc))))
		return (NULL);
	elem->next = NULL;
	elem->name = (char *)malloc(129 * sizeof(char));
	if (nb)
	{
		if (nb <= *used_nb)
			exit(write(1, "numero de champion deja utilise\n", 31));
		elem->nb_champ = nb;
	}
	else
	{
		elem->nb_champ = (*used_nb) + 1;
		(*used_nb)++;
	}
	elem->size = 0;
	elem->desc = (char *)malloc(2049 * sizeof(char));
	return (elem);
}

t_desc		*create_desc(t_desc **desc, int nb)
{
	static int used_nb;

	if (!*desc)
	{
		if (!(*desc = (t_desc *)malloc(sizeof(t_desc))))
			return (NULL);
		(*desc)->next = NULL;
		(*desc)->name = (char *)malloc(129 *sizeof(char));
		(*desc)->size = 0;
		if (nb)
			(*desc)->nb_champ = nb;
		if (nb == 1)
			used_nb = 1;
		(*desc)->desc = (char *)malloc(2049 *sizeof(char));
		return (*desc);
	}
	return(create_desc2(desc, nb, &used_nb));
}

t_list		*create_elem(t_list *begin, int champ_nb, int pc)
{
	if (!begin)
	{
		if (!(begin = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		ft_bzero((begin)->reg_number, REG_NUMBER);
		(begin)->prev = NULL;
		(begin)->next = NULL;
		(begin)->pc = 0;
		(begin)->reg_number[0] = champ_nb;
		(begin)->carry = 0;
		(begin)->process_nb = 0;
		(begin)->action_time = 0;
		return (begin);
	}
	if (!((begin)->prev = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	ft_bzero((begin)->reg_number, REG_NUMBER);
	(begin)->prev->next = (begin);
	(begin)->prev->prev = NULL;
	(begin)->prev->pc = pc;
	(begin)->prev->reg_number[0] = champ_nb;
	(begin)->prev->carry = 0;
	(begin)->prev->process_nb++;
	(begin)->prev->action_time = 0;
	begin = (begin)->prev;
	return (begin);
}

int			check_flag(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!strcmp(argv[1], "-v"))
			data->flag_visu = 1;
		i++;
	}
	return (0);
}

void		init_struct(t_data *data)
{
	int		i;

	i = 0;
	ft_bzero(data->map, MEM_SIZE);
	data->flag_slowmode = 0;
	data->flag_visu = 0;
	data->cycle = 0;
	data->cycle_to_die = CYCLE_TO_DIE;
	data->cycle_to_die_nbr = 1;
	data->begin = NULL;
	data->desc = NULL;
	data->nb_champ = 0;
	data->live_cpt = 0;
//	init_pt_tab(data->tab);
	while (i <= MAX_PLAYERS + 1)
	{
//		data->statut_champ[i] = 0;
//		data->tab_live[i++] = 0;
		i++;
	}
}
