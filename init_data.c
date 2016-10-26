/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 16:27:09 by jle-quer          #+#    #+#             */
/*   Updated: 2016/10/26 15:32:27 by lbaudran         ###   ########.fr       */
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
	ft_bzero((begin->prev)->reg_number, REG_NUMBER);
	(begin)->prev->next = (begin);
	(begin)->prev->prev = NULL;
	(begin)->prev->pc = pc;
	(begin)->prev->reg_number[0] = champ_nb;
	(begin)->prev->carry = 0;
	((begin)->prev->process_nb) = (begin->process_nb)++;
	(begin)->prev->action_time = 0;
	return (begin->prev);
}

int			check_flag(int argc, char **argv, t_data *data)
{
	int	i;

/*
 * j'ai l'impression que tu t'est gourer dans ta fonction et que tu voulais mettre
 * av[i] plutot que av[1] ? dans le doute je touche a rien ^^
 *
 * C'etait une erreur effectivement, la fonction a ete faite dans le cas ou on aurait
 * rajouter des autres flags, pour le moment je la laisse;;
 */
	i = 1;
	while (i < argc)
	{
		if (!strcmp(argv[i], "-v"))
			data->flag_visu = 1;
		i++;
	}
	return (0);
}

void		init_structur(t_data *data)
{
	int		i;

	i = 0;
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
//	init_pt_tab(data->tab);
	while (i <= MAX_PLAYERS + 1)
	{
//		data->statut_champ[i] = 0;
//		data->tab_live[i++] = 0;
		i++;
	}
}
