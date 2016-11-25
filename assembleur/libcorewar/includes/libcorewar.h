/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcorewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vijacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:42:18 by vijacque          #+#    #+#             */
/*   Updated: 2016/11/25 15:01:05 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCOREWAR_H
# define LIBCOREWAR_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFF_SIZE	1
# define OK			0
# define OPENFAIL	1
# define READFAIL	2
# define MALLOCFAIL	3

int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
void	ft_putendl(char *str);
void	ft_putnbr(int n);
void	ft_puttab(char **tab);
void	ft_putchar(char c);
int		is_slash(char *s);
void	ft_putstr(char *str);
int		get_next_line(int const fd, char **line);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	ft_strclr(char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_bzero(void *s, size_t n);
void	*ft_malloc(int nombre);
char	*ft_strdup(const char *s1);
void	ft_trim(char **s);
char	**ft_strsplit(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_tablen(char **tab);
int		ft_isdigit_str(char *str);
int		ft_isdigit(int c);
char	*ft_strcpy(char *dst, const char *src);
int		ft_linelen(char *str);

#endif
