/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:55:08 by jle-quer          #+#    #+#             */
/*   Updated: 2016/12/06 12:40:55 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_desc		*create_desc2(t_desc **desc, int nb)
{
	t_desc		*elem;
	static int	*tab = NULL;

	if (tab == NULL)
	{
		tab = malloc(sizeof(int) * 4);
		init_tab(tab);
	}
	elem = *desc;
	tab[0] = elem->nb_champ;
	while (elem->next)
		elem = (elem)->next;
	if (!(elem->next = (t_desc *)malloc(sizeof(t_desc))))
		return (NULL);
	elem->next->next = NULL;
	elem->next->name = (char *)malloc(sizeof(char) * 129);
	if (nb)
		elem->next->nb_champ = is_used(nb, tab);
	else
		elem->next->nb_champ = find_first_nb(tab);
	elem->next->size = 0;
	elem->next->desc = (char *)malloc(sizeof(char) * 2049);
	elem->next->dead = 0;
	elem->next->live = 0;
	return (elem->next);
}

t_desc		*create_desc(t_desc **desc, int nb)
{
	if (!*desc)
	{
		if (!(*desc = (t_desc *)malloc(sizeof(t_desc))))
			return (NULL);
		(*desc)->next = NULL;
		(*desc)->name = (char *)malloc(sizeof(char) * 129);
		(*desc)->size = 0;
		if (nb)
			(*desc)->nb_champ = nb;
		else
			(*desc)->nb_champ = 1;
		(*desc)->desc = (char *)malloc(sizeof(char) * 2049);
		(*desc)->dead = 0;
		(*desc)->live = 0;
		return (*desc);
	}
	return (create_desc2(desc, nb));
}

t_list		*create_elem2(t_list *begin, int champ_nb, int pc)
{
	if (!(begin->prev = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	begin->prev->reg_number = ft_memalloc((size_t)(4 * REG_NUMBER));
	begin->prev->next = begin;
	begin->prev->prev = NULL;
	begin->prev->pc = pc;
	begin->prev->reg_number[0] = champ_nb;
	begin->prev->carry = 0;
	begin->prev->process_nb = begin->process_nb + 1;
	begin->prev->action_time = 0;
	begin->prev->live = 0;
	begin->prev->nb_champ = champ_nb;
	return (begin->prev);
}

t_list		*create_elem(t_list *begin, int champ_nb, int pc)
{
	if (!begin)
	{
		if (!(begin = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		begin->reg_number = ft_memalloc((size_t)(4 * REG_NUMBER));
		begin->prev = NULL;
		begin->next = NULL;
		begin->pc = 0;
		begin->reg_number[0] = champ_nb;
		begin->carry = 0;
		begin->process_nb = 0;
		begin->action_time = 0;
		begin->live = 0;
		begin->nb_champ = champ_nb;
		return (begin);
	}
	return (create_elem2(begin, champ_nb, pc));
}

void		init_structur(t_data *data)
{
	data->flag_dump = -1;
	data->last_live_nb_champ = 0;
	ft_bzero(data->map, MEM_SIZE - 1);
	data->flag_slowmode = 0;
	data->flag_visu = 0;
	data->cycle = 0;
	data->cycle_to_die = CYCLE_TO_DIE;
	data->ctd_nbr = 1;
	data->begin = NULL;
	data->desc = NULL;
	data->nb_champ = 0;
	data->live_cpt = 0;
	data->display = NULL;
}
