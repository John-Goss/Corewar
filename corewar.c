/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 12:56:03 by lbaudran          #+#    #+#             */
/*   Updated: 2016/09/22 14:11:53 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 1;
	init_struct(&data);
	check_flag(argc, argv, &data);
	parse_map(argc, argv, &data);
	exit(0);
	verif_valid(argc, argv, &data);
	if (data.flag_visu)
	{
		aff_window();
//		initscr();
//		if (getch() == ' ')
//			data.flag_slowmode = 1;
	}
	while (42)
	{
		turn(&data);
		(data.cycle)++;
		if ((--(data.cycle_to_die)) == 0)
			if (verif_end(&data) == 1)
				break;
	}
//	end(data);
}

void		stock_desc(t_data *data, char *buf)
{
	create_desc()
}

void		recup_champ(t_data *data, char **argv, int i)
{
	int			fd;
	char		buf[BUFF_SIZE + 1];
	static int	n = 0;

	buf[BUFF_SIZE] = '\0';
	fd = open(argv[i], O_RDONLY);
	read(fd, buf, BUFF_SIZE);
	stock_desc(data, buf);
	while(!(read(fd, data->map + n, 1)) && n <= MEM_SIZE)
		n++;
	if (n > MEM_SIZE)
		exit(write(1, "Taille champion incorrecte\n", 27));
	if (n % CHAMP_MAX_SIZE)
		n = ((n / CHAMP_MAX_SIZE)+ 1) * CHAMP_MAX_SIZE;
	n++;
}


void		parse_map(int argc, char **argv, t_data *data)
{
	int		i;

	i = 1 + data->flag_visu;
	while (i < argc)
		recup_champ(data, argv, i++);

}

void		turn(t_data *data)
{
	t_list *elem;

	elem = data->begin;
	while (elem)
	{
		if (data->flag_slowmode == 1)
			getch();
//		process_action(data, elem);
		elem = elem->next;
	}
	return ;
}

t_list		*destroy_elem(t_list *elem)
{
	t_list *tmp;

	tmp = elem->next;
	tmp->prev = elem->prev;
	tmp->prev->next = tmp;
	free(elem);
	return (tmp);
}

void		check_who_is_alive(t_data *data)
{
	int		i;
	t_list	*elem;

	elem = data->begin;
	i = 1;
	while (i < data->nb_champ)
	{
		if (data->tab_live[i] < NBR_LIVE)
			data->statut_champ[i] = 1;
		i++;
	}
	while (elem)
	{
		if (elem->live == 0)
			elem = destroy_elem(elem);
		else
			elem = elem->next;
	}
	return ;
}

int			verif_end(t_data *data)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	data->cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * data->cycle_to_die_nbr);
	data->cycle_to_die_nbr++;
	check_who_is_alive(data);
	while (i < data->nb_champ)
	{
		if (data->statut_champ[i++] == 0)
			j++;
		if (j >= 2)
			return (0);
	}
	return (1);
}

int			verif_valid(int argc, char **argv, t_data *data)
{
	t_desc *elem;

	(void)argc;
	(void)argv;
	elem = data->desc;;
	if (data->nb_champ > MAX_PLAYERS + 1)
		exit(write(1, "Nombre de champions incorrect\n", 30));
	while (elem)
	{
		if (elem->size > CHAMP_MAX_SIZE)
			exit(write(1, "Taille champion incorrecte\n", 27));
		elem = elem->next;
	}
	return (0);
}
