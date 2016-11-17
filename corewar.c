/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 12:56:03 by lbaudran          #+#    #+#             */
/*   Updated: 2016/11/17 14:39:26 by jle-quer         ###   ########.fr       */
/*   Updated: 2016/11/03 18:08:29 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		end(t_data *data)
{
	t_desc	*elem;

	elem = data->desc;
	if (data->flag_visu == 1)
		delete_win(data->display);
	if (data->last_live_nb_champ)
	{
		while (elem && elem->nb_champ != data->last_live_nb_champ)
			elem = elem->next;
		ft_printf("Le joueur %d (%s) a gagne\n", elem->nb_champ, elem->name);
	}
	else
		exit(write(1, "Aucun live n'a ete fait\n", 24));
}

int			main(int argc, char **argv)
{
	t_data	data;

	init_structur(&data);
	check_flag(argc, argv, &data);
	parse_map(argc, argv, &data);
	if (data.flag_visu == 1)
	{
		get_str_addr(data.map);
		aff_window(&data);
	}
	data.flag_slowmode == 1 ? turn_by_slowmode(&data) : turn_by_none(&data);
	end(&data);
}

int			stock_desc(t_data *data, char *buf, int nb)
{
	unsigned int		i;
	t_desc				*elem;

	i = 0;
	elem = create_desc(&data->desc, nb);
	i = (buf[0] << 24 & 0xff000000) | (buf[1] << 16 & 0xff0000) |
		(buf[2] << 8 & 0xff00) | (buf[3] & 0xff);
	if (i != COREWAR_EXEC_MAGIC)
		exit(write(1, "magic invalid\n", 14));
	ft_strncpy(elem->name, buf + 4, 128);
	elem->size = (buf[136] << 24 & 0xff000000) | (buf[137] << 16 & 0xff0000) |
		(buf[138] << 8 & 0xff00) | (buf[139] & 0xff);
	ft_strcpy(elem->desc, buf + 140);
	return (elem->size);
}

int			recup_champ_nb(t_desc *begin)
{
	t_desc *elem;

	elem = begin;
	while (elem->next)
		elem = elem->next;
	return (elem->nb_champ);
}

void		recup_champ(t_data *data, char **argv, int i, int nb)
{
	int			fd;
	char		buf[BUFF_SIZE + 1];
	static int	n = 0;
	int			size[2];

	buf[BUFF_SIZE] = '\0';
	fd = open(argv[i], O_RDONLY);
	if (fd == -1)
		exit(ft_printf("Invalid path\n"));
	read(fd, buf, BUFF_SIZE);
	size[0] = stock_desc(data, buf, nb);
	size[1] = n;
	data->begin = create_elem(data->begin, recup_champ_nb(data->desc), n);
	while ((read(fd, data->map + n, 1)) && n <= MEM_SIZE)
	{
		n++;
	}
	if (n > MEM_SIZE)
		exit(write(1, "Taille champion trop grande\n", 27));
	size[1] = n - size[1];
	if (size[0] != size[1])
		exit(write(1, "Taille indiquee incorrecte\n", 27));
	if (size[0] > CHAMP_MAX_SIZE)
		exit(write(1, "Taille champion incorrecte\n", 27));
	n = (n / (MEM_SIZE / data->nb_champ) + 1) * (MEM_SIZE / data->nb_champ);
}

void			is_number_set(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!(ft_strcmp(argv[i], "-n")))
			data->nb_champ -= 1;
			if (!(test_int(argv[i])))
			data->nb_champ -= 1;
		i++;
	}
}

void		parse_map(int argc, char **argv, t_data *data)
{
	int		i;
	int		nb;

	nb = 0;
	i = 1 + data->flag_visu;
	data->nb_champ = argc - 1 - data->flag_visu;
	is_number_set(argc, argv, data);
	if (data->flag_dump >= 0)
	{
		data->nb_champ -= 2;
		i += 2;
	}
	if (i == argc)
	{
		ft_printf("NO CHAMPIONS\n");
		exit(0);
	}
	while (i < argc)
	{
		if (!(ft_strcmp(argv[i], "-n")))
		{
			i++;
			if (test_int(argv[i]))
				exit(ft_printf("Numero de champion incorrect.\n"));
			nb = ft_atoi(argv[i]);
			i++;
		}
		recup_champ(data, argv, i++, nb);
		nb = 0;
	}
}

void		adjust_action_time(t_list *elem, char pc)
{
	if (pc == 0x01 || pc == 0x04 || pc == 0x05 || pc == 0x0D)
		elem->action_time = 10;
	else if (pc == 0x02 || pc == 0x03)
		elem->action_time = 5;
	else if (pc == 0x06 || pc == 0x07 || pc == 0x08)
		elem->action_time = 6;
	else if (pc == 0x0A || pc == 0x0B)
		elem->action_time = 25;
	else if (pc == 0x09)
		elem->action_time = 20;
	else if (pc == 0x0C)
		elem->action_time = 800;
	else if (pc == 0x0E)
		elem->action_time = 50;
	else if (pc == 0x0F)
		elem->action_time = 1000;
	else if (pc == 0x10)
		elem->action_time = 2;
}

void		process_action(t_data *data, t_list *elem)
{
	if ((!(data->map[elem->pc] >= 0x01 && data->map[elem->pc] <= 0x10)) &&
			!elem->action_time)
	{
		(elem->pc)++;
		return ;
	}
	else
	{
		if (!(elem->action_time))
			adjust_action_time(elem, data->map[elem->pc]);
		if (elem->action_time)
		{
			elem->action_time--;
			if (!(elem->action_time))
				instruction_exec(data, elem);
		}
	}
}

void		turn(t_data *data)
{
	t_list *elem;

	if (data == NULL || data->begin == NULL)
		return ;
	elem = data->begin;
	while (elem)
	{
		process_action(data, elem);
		elem = elem->next;
	}
	return ;
}

t_list		*destroy_elem(t_data *data,t_list *elem)
{
	t_list *tmp;

	tmp = elem->next;
	if (elem->next == NULL)
	{
		if (elem->prev)
			elem->prev->next = NULL;
		free(elem);
		data->begin = NULL;
		return(NULL);
	}
	if (elem->prev)
	{
		tmp->prev = elem->prev;
		tmp->prev->next = tmp;
	}
	else
	{
		data->begin = elem->next;
		if (data->begin)
		{
			data->begin->prev = NULL;
			free(elem);
			return(data->begin);
		}
		else
			data->begin = NULL;
		free(elem);
		return(NULL);
	}
	free(elem);
	return (tmp);
}

void		check_who_is_alive(t_data *data)
{
	int		i;
	t_list	*elem;

	elem = data->begin;
	i = 1;
	while (elem)
	{
		if (elem->live == 0)
			elem = destroy_elem(data,elem);
		else
		{
			elem->live = 0;
			elem = elem->next;
		}
	}
	return ;
}

int			verif_end(t_data *data)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (data->check == MAX_CHECKS || data->live_cpt >= NBR_LIVE)
	{
		if (data->check == MAX_CHECKS)
			data->check = 0;
		data->cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * data->ctd_nbr);
		data->ctd_nbr++;
		check_who_is_alive(data);
	}
	else
	{
		(data->check)++;
		data->cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * data->ctd_nbr);
		check_who_is_alive(data);
	}
	data->live_cpt = 0;
	if (data->begin)
		return (0);
	return(1);
}
