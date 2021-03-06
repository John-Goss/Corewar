/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vijacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:31:26 by vijacque          #+#    #+#             */
/*   Updated: 2016/10/12 13:31:27 by vijacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcorewar.h>

void	ft_strclr(char *s)
{
	if (s)
		ft_bzero(s, ft_strlen(s));
}
