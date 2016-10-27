/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vijacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:31:49 by vijacque          #+#    #+#             */
/*   Updated: 2016/10/12 13:31:50 by vijacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcorewar.h>

char		*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1 && !s2)
	{
		dest = NULL;
		return (dest);
	}
	dest = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!dest)
		return (NULL);
	if (s1)
		while (s1[i])
			dest[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			dest[j++] = s2[i++];
	dest[j] = '\0';
	return (dest);
}
