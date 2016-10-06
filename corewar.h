/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 12:15:43 by lbaudran          #+#    #+#             */
/*   Updated: 2016/10/05 15:52:01 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ** Toutes les tailles sont en octets.
 * ** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
 * */

#define IND_SIZE			2
#define REG_SIZE			4
#define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

#define MAX_ARGS_NUMBER		4
#define MAX_PLAYERS			4
#define MEM_SIZE			(4 * 1024)
#define IDX_MOD				(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

#define COMMENT_CHAR		'#'
#define LABEL_CHAR			':'
#define DIRECT_CHAR			'%'
#define SEPARATOR_CHAR		','

#define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING		".name"
#define COMMENT_CMD_STRING	".comment"

#define REG_NUMBER			16

#define CYCLE_TO_DIE		1536
#define CYCLE_DELTA			50
#define NBR_LIVE			21
#define MAX_CHECKS			10

/*
 * **
 * */

typedef char				t_arg_type;

#define T_REG				1
#define T_DIR				2
#define T_IND				4
#define T_LAB				8

/*
 * **
 * */

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3
# define BUFF_SIZE			(4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH + 2 + 6)

#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "Libft/INCLUDES/libft.h"

typedef struct				header_s
{
	unsigned int			magic;
	char					prog_name[PROG_NAME_LENGTH + 1];
	unsigned int			prog_size;
	char					comment[COMMENT_LENGTH + 1];
}							header_t;

typedef struct				s_list
{
	struct s_list			*next;
	struct s_list			*prev;
	int						pc;
	int						process_nb;
	int						live;
	int						carry;
	int						action_time;
	int						reg_number[REG_NUMBER];
}							t_list;

typedef struct				s_desc
{
	char					*name;
	char					*desc;
	int						nb_champ;
	unsigned int			size;
	struct s_desc			*next;
}							t_desc;

typedef struct				s_data
{
	void					(*tab[17])(struct s_data *data, t_list *elem);
	int						flag_slowmode;
	int						flag_visu;
	int						cycle;
	int						cycle_to_die;
	int						live_cpt;
	int 					cycle_to_die_nbr;
	t_list					*begin;
	t_desc					*desc;
	int						check;
	unsigned char			map[MEM_SIZE];
	int						last_live_nb_champ;
	int						champ[MAX_PLAYERS + 1];
	int						nb_champ;
}							t_data;

typedef struct				s_display
{
	WINDOW					*screen;
	WINDOW					*win;
	unsigned char			*mem;
}							t_display;

/*
 * PROTOTYPE
 */

int							check_flag(int argc, char **argv, t_data *data);
void						init_struct(t_data *data);
int							verif_valid(int argc, char **argv, t_data *data);
void						turn(t_data *data);
int							verif_end(t_data *data);
void						check_who_is_alive(t_data *data);
void						parse_map(int argc, char **argv, t_data *data);
void						init_pt_tab(void (**tab)(t_data *data,
							t_list *elem));

unsigned char				*get_str_addr(unsigned char *mem);
WINDOW						*get_win_addr(WINDOW *window);

t_list						*create_elem(t_list **begin, int champ_nb, int pc);
t_desc						*create_desc(t_desc **desc, int nb);

/*
 *	PROTOTYPE INSTRUCTIONS
 */

void		apply_live(t_data *data, t_list *elem);
void		apply_ld(t_data *data, t_list *elem, int *params);
void		apply_st(t_data *data, t_list *elem, int *params);
void		apply_add(t_data *data, t_list *elem);
void		apply_sub(t_data *data, t_list *elem);
void		apply_and(t_data *data, t_list *elem);
void		apply_or(t_data *data, t_list *elem);
void		apply_xor(t_data *data, t_list *elem);
void		apply_zjmp(t_data *data, t_list *elem);
void		apply_ldi(t_data *data, t_list *elem);
void		apply_sti(t_data *data, t_list *elem);
void		apply_fork(t_data *data, t_list *elem);
void		apply_lld(t_data *data, t_list *elem);
void		apply_lldi(t_data *data, t_list *elem);
void		apply_lfork(t_data *data, t_list *elem);
void		apply_aff(t_data *data, t_list *elem);

/*
 * PROTOTYPE DISPLAY
 */

int							*set_array_pc(t_data *data);
int							aff_window(t_data *data);
