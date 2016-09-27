/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:22:47 by jle-quer          #+#    #+#             */
/*   Updated: 2016/09/26 15:55:25 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	set_buf(char *mem)
{
	int	i;
	int	cpt;

	i = 65;
	cpt = 0;
	bzero(mem, MEM_SIZE + 1);
	while (cpt < MEM_SIZE)
	{
		mem[cpt++] = i++;
		if (i == 91)
			i = 65;
	}
	if (cpt == MEM_SIZE)
		return (0);
	else
		return (1);
}

int	main()
{
	char	buf[MEM_SIZE + 1];

	buf[MEM_SIZE] = '\0';
	if (set_buf(buf) == 1)
	{
		printf("ERREUR\n");
		exit(1);
	}
	aff_window(buf);
	return (0);
}
