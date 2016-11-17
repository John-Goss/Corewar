/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 16:27:09 by jle-quer          #+#    #+#             */
/*   Updated: 2016/11/17 14:48:14 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		test_int(char *s)
{
	long long	i;
	int			n;
	int			signe;

	signe = 1;
	n = 0;
	i = 0;
	if (!s)
		return (0);
	if (s[n] == '-')
	{
		n++;
		signe = -1;
	}
	while (s[n])
	{
		if (s[n] > '9' || s[n] < '0')
			return (1);
		i *= 10;
		i += s[n++] - '0';
	}
	i *= signe;
	if (i < 2147483647 && i > -2147483648)
		return (0);
	return (1);
}

void	init_tab(int *tab)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		tab[i++] = 0;
	}
}

int			find_first_nb(int *tab)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (tab[i] != 0 && i < 4)
	{
		if (tab[i] == j)
		{
			j++;
			i = 0;
		}
		else
			i++;
	}
	tab[i] = j;
	return(j);
}

int			is_used(int nb, int *tab)
{
	int i;

	i = 0;
	while (tab[i] != 0 && i < 4)
	{
		if (tab[i] == nb)
			exit(write(1, "numero de champion deja utilise\n", 31));
		i++;
	}
	tab[i] = nb;
	return(1);
}
t_desc		*create_desc2(t_desc **desc, int nb)
{
	t_desc		*elem;
	static int	start = 0;
	static int	*tab;

	if (start++ == 0)
	{
		tab = malloc(4 * sizeof(int));
		init_tab(tab);
	}
	elem = *desc;
	tab[0] = elem->nb_champ;
	while (elem->next)
		elem = (elem)->next;
	if (!(elem->next = (t_desc *)malloc(sizeof(t_desc))))
		return (NULL);
	(elem)->next->next = NULL;
	(elem)->next->name = (char *)malloc(129 * sizeof(char));
	if (nb)
	{
		is_used(nb, tab);
		(elem)->next->nb_champ = nb;
	}
	else
		elem->next->nb_champ = find_first_nb(tab);
	(elem)->next->size = 0;
	(elem)->next->desc = (char *)malloc(2049 * sizeof(char));
	return (elem->next);
}

t_desc		*create_desc(t_desc **desc, int nb)
{
	if (!*desc)
	{
		if (!(*desc = (t_desc *)malloc(sizeof(t_desc))))
			return (NULL);
		(*desc)->next = NULL;
		(*desc)->name = (char *)malloc(129 *sizeof(char));
		(*desc)->size = 0;
		if (nb)
			(*desc)->nb_champ = nb;
		else
			(*desc)->nb_champ = 1;
		(*desc)->desc = (char *)malloc(2049 *sizeof(char));
		return (*desc);
	}
	return(create_desc2(desc, nb));
}

t_list		*create_elem(t_list *begin, int champ_nb, int pc)
{
	if (!begin)
	{
		if (!(begin = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		begin->reg_number = ft_memalloc(REG_NUMBER * 4);
		(begin)->prev = NULL;
		(begin)->next = NULL;
		(begin)->pc = 0;
		(begin)->reg_number[0] = champ_nb;
		(begin)->carry = 0;
		(begin)->process_nb = 0;
		(begin)->action_time = 0;
		(begin)->live = 0;
		begin->nb_champ = champ_nb;
		return (begin);
	}
	if (!((begin)->prev = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	(begin->prev)->reg_number = malloc(REG_NUMBER * sizeof(int));
	ft_bzero((begin->prev)->reg_number, REG_NUMBER);
	(begin)->prev->next = (begin);
	(begin)->prev->prev = NULL;
	(begin)->prev->pc = pc;
	(begin)->prev->reg_number[0] = champ_nb;
	(begin)->prev->carry = 0;
	((begin)->prev->process_nb) = (begin->process_nb) + 1;
	(begin)->prev->action_time = 0;
	(begin)->prev->live = 0;
	begin->prev->nb_champ = champ_nb;
	return (begin->prev);
}

int			check_flag(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-v"))
			data->flag_visu = 1;
		if (!ft_strcmp(argv[i], "-dump"))
		{
			i++;
			if (!test_int(argv[i]))
				data->flag_dump = ft_atoi(argv[i]);
			else
			{
				ft_printf("Incorrect value for dump\n");
				exit(0);
			}
		}
		i++;
	}
	if (data->flag_visu && data->flag_dump > -1)
	{
		ft_printf("Too many flags\n");
		exit(0);
	}
	return (0);
}

void		init_structur(t_data *data)
{
	int		i;

	i = 0;
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
	while (i <= MAX_PLAYERS + 1)
	{
//		data->statut_champ[i] = 0;
//		data->tab_live[i++] = 0;
		i++;
	}
}
