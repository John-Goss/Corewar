/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vijacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 17:00:07 by vijacque          #+#    #+#             */
/*   Updated: 2016/10/11 17:00:09 by vijacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcorewar.h>

void	*ft_malloc(int nombre)
{
	void	*str;

	str = malloc(nombre);
	if (str == NULL)
	{
		ft_putendl("Error malloc");
		exit(MALLOCFAIL);
	}
	return (str);
}
