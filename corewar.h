/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 12:15:43 by lbaudran          #+#    #+#             */
/*   Updated: 2016/09/22 12:43:48 by jle-quer         ###   ########.fr       */
/*   Updated: 2016/09/19 15:52:01 by lbaudran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ** Toutes les tailles sont en octets.
 * ** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
 * */

#define IND_SIZE			4
#define REG_SIZE			8
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

# define BUFF_SIZE			(4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH)
# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

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
	int						champ_nb;
	int						process_nb;
	int						live;
	int						carry;
	int						action_time;
}							t_list;

typedef struct				s_desc
{
	char					*name;
	char					*desc;
	unsigned int			size;
	struct s_desc			*next;
}							t_desc;

typedef struct				s_data
{
	int						flag_slowmode;
	int						flag_visu;
	int						cycle;
	int						cycle_to_die;
	int						live_cpt;
	int 					cycle_to_die_nbr;
	t_list					*begin;
	t_desc					*desc;
	char					map[MEM_SIZE];
	int						tab_live[MAX_PLAYERS + 1];
	int						statut_champ[MAX_PLAYERS + 1];
	int						nb_champ;
}							t_data;


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

t_list						*create_elem(t_list **begin, int champ_nb, int pc);

/*
 * PROTOTYPE DISPLAY
 */

int							aff_window(void);
