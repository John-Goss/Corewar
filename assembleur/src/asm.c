/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vijacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:59:12 by vijacque          #+#    #+#             */
/*   Updated: 2016/11/25 14:38:08 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void		make_header(t_env *e)
{
	int	i;

	e->head.magic = COREWAR_EXEC_MAGIC;
	e->head.prog_size = e->prog_size;
	i = 0;
	while (i <= PROG_NAME_LENGTH)
	{
		e->head.prog_name[i] = 0;
		i++;
	}
	ft_strcpy(e->head.prog_name, e->info[0]);
	i = 0;
	while (i <= COMMENT_LENGTH)
	{
		e->head.comment[i] = 0;
		i++;
	}
	ft_strcpy(e->head.comment, e->info[1]);
}

static int		launch_with_path(t_env *e, int ac, char **av)
{
	if (ac == 4)
	{
		e->info[0] = "";
		e->info[1] = "";
		e->ins = read_champ(e, av[3], NULL, NULL);
		delete_separator_char(e->ins);
		checks(e);
		encode(e);
		make_header(e);
		write_file(e, av[3], av[2]);
	}
	return (0);
}

static int		launch_without_path(t_env *e, char *arg)
{
	e->info[0] = "";
	e->info[1] = "";
	e->ins = read_champ(e, arg, NULL, NULL);
	delete_separator_char(e->ins);
	checks(e);
	encode(e);
	make_header(e);
	write_file_without_path(e, arg);
	return (0);
}

static int		check_ext(char *s, int check)
{
	int i;

	i = ft_strlen(s);
	if (check == 2)
		if ((s[i - 2] == '.') && (s[i - 1] == 's'))
			return (1);
	if (check == 3)
		if ((s[i - 1] == '/') && (i > 1))
			return (1);
	return (0);
}

int				main(int ac, char **av)
{
	t_env		*e;

	if ((e = (t_env*)ft_malloc(sizeof(t_env))) == NULL)
		ft_exit("MALLOC failed.", 0);
	if (ac == 4)
	{
		if ((ft_strcmp(av[1], "-n") == 0) && (check_ext(av[3], 2) == 1) \
				&& (check_ext(av[2], 3) == 1))
			launch_with_path(e, ac, av);
		else
			ft_exit("bad extension or missing the -n option", 0);
	}
	else if (ac == 2)
	{
		if (check_ext(av[1], 2) == 1)
			launch_without_path(e, av[1]);
		else
			ft_exit("bad extension", 1);
	}
	else
		ft_exit("Bad number of arguments", 0);
}
