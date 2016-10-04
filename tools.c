/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 12:56:09 by jle-quer          #+#    #+#             */
/*   Updated: 2016/09/29 13:48:23 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*get_str_addr(char *mem)
{
	static char	*ptr = NULL;

	if (mem)
		ptr = mem;
	return (ptr);
}

WINDOW	*get_win_addr(WINDOW *window)
{
	static WINDOW	*ptr = NULL;

	if (window)
		ptr = window;
	return (ptr);
}

void	print_hex(unsigned char c)
{
	if (c / 16 < 10)
		ft_putnbr(c / 16);
	else
		ft_putchar('a' + (c / 16 - 10));
	if (c % 16 < 10)
		ft_putnbr(c % 16);
	else
		ft_putchar('a' + (c % 16 - 10));
	ft_putchar(' ');
}

int		ft_sqrt(int c)
{
	int x;

	x = 0;
	while (x * x < c)
		x++;
	return (x); 
}

void	ft_print_mem(unsigned char *str)
{
	int	x;

	x = 0;
	while (x < MEM_SIZE)
	{
		print_hex(str[x]);
		if ((x + 1) % ft_sqrt(MEM_SIZE) == 0)
			ft_putchar('\n');
		x++;
	}
}
