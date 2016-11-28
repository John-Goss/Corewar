/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaudran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 12:15:43 by lbaudran          #+#    #+#             */
/*   Updated: 2016/11/28 14:04:43 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef COREWAR_H
# define COREWAR_H

# include <stdlib.h>
# include <unistd.h>
# include <ncurses.h>
# include <curses.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <libft.h>

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4 * 1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

typedef char				t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3
# define BUFF_SIZE			(4 + PROG_NAME_LENGTH + 4 + COMMENT_LENGTH + 2 + 6)

typedef struct				s_header
{
	unsigned int			magic;
	char					prog_name[PROG_NAME_LENGTH + 1];
	unsigned int			prog_size;
	char					comment[COMMENT_LENGTH + 1];
}							t_header;

typedef struct				s_list
{
	struct s_list			*next;
	struct s_list			*prev;
	int						pc;
	int						process_nb;
	int						live;
	int						carry;
	int						action_time;
	int						nb_champ;
	int						*reg_number;
	int						dir_by;
}							t_list;

typedef struct				s_desc
{
	char					*name;
	char					*desc;
	int						nb_champ;
	int						pc;
	unsigned int			size;
	struct s_desc			*next;
}							t_desc;

typedef struct				s_display
{
	WINDOW					*screen;
	WINDOW					*win;
	WINDOW					*info;
	WINDOW					*header;
	unsigned char			*mem;
}							t_display;

typedef struct				s_data
{
	int						flag_dump;
	int						flag_slowmode;
	int						flag_visu;
	int						cycle;
	int						cycle_to_die;
	long					live_cpt;
	int						ctd_nbr;
	t_list					*begin;
	t_desc					*desc;
	t_display				*display;
	int						check;
	unsigned char			map[MEM_SIZE];
	int						last_live_nb_champ;
	int						champ[MAX_PLAYERS + 1];
	int						nb_champ;
	int						dep;
}							t_data;

/*
** PROTOTYPE
*/

int							check_flag(int argc, char **argv, t_data *data);
void						init_structur(t_data *data);
int							verif_valid(int argc, char **argv, t_data *data);
void						turn(t_data *data);
int							verif_end(t_data *data);
void						check_who_is_alive(t_data *data);
void						parse_map(int argc, char **argv, t_data *data);
void						init_pt_tab(void (**tab)(t_data *data,
							t_list *elem));
int							test_int(char *s);

int							turn_by_none(t_data *data);
int							turn_by_slowmode(t_data *data);
unsigned char				*get_str_addr(unsigned char *mem);
WINDOW						*get_win_addr(WINDOW *window);

t_list						*create_elem(t_list *begin, int champ_nb, int pc);
t_desc						*create_desc(t_desc **desc, int nb);
void						end(t_data *data);

/*
** PROTOTYPE INSTRUCTIONS
*/

void						instruction_exec(t_data *data, t_list *elem);
unsigned int				get_dir_value(t_data *data, t_list *elem,
		int *prm_pos);
unsigned int				get_ind_value(t_data *data, t_list *elem,
		int prm_pos);
unsigned int				trans_four_bytes(char *transfer_bytes);
char						*get_dir_value_quatre(t_data *data, t_list *elem,
		int prm_pos);

void						apply_live(t_data *data, t_list *elem);
void						apply_ld(t_data *data, t_list *elem,
		unsigned int *params, unsigned int *param_type);
void						apply_st(t_data *data, t_list *elem,
		unsigned int *params, unsigned int *param_type);
void						apply_add(t_data *data, t_list *elem,
		unsigned int *params, unsigned int *param_type);
void						apply_sub(t_data *data, t_list *elem,
		unsigned int *params, unsigned int *param_type);
void						apply_and(t_data *data, t_list *elem,
		unsigned int *params, unsigned int *param_type);
void						apply_or(t_data *data, t_list *elem,
		unsigned int *params, unsigned int *param_type);
void						apply_xor(t_data *data, t_list *elem,
		unsigned int *params, unsigned int *param_type);
void						apply_zjmp(t_data *data, t_list *elem,
		unsigned int *params);
void						apply_ldi(t_data *data, t_list *elem,
		unsigned int *param_type, unsigned int *params);
void						apply_sti(t_data *data, t_list *elem,
		unsigned int *param_type, unsigned int *params);
void						apply_fork(t_data *data, t_list *elem,
		unsigned int *params);
void						apply_lld(t_data *data, t_list *elem,
		unsigned int *param_type, unsigned int *params);
void						apply_lldi(t_data *data, t_list *elem,
		unsigned int *param_type, unsigned int *params);
void						apply_lfork(t_data *data, t_list *elem,
		unsigned int *params);
void						apply_aff(t_data *data, t_list *elem,
		unsigned int *params);

unsigned int				*type_tab_make(char *types_bin,
		unsigned int *type_tab);
char						*conv_dec_to_bin(int n);
char						*rev_str(char *string);
int							two_or_four(t_data *data, t_list *elem);
unsigned int				trans_two_bytes(char *transfer_bytes);
char						*get_two_bytes(t_data *data, t_list *elem,
		int prm_pos);
unsigned int				*get_params(unsigned int *par_types, t_data *data,
		t_list *elem);
unsigned int				*det_types(t_data *data, t_list *elem,
		unsigned int parameter_types);

void						init_tab(int *tab);
int							is_used(int nb, int *tab);
int							find_first_nb(int *tab);

/*
** PROTOTYPE DISPLAY
*/

int							champ_id(t_data *data, int index);
int							nb_champ_pc(t_list *list, int value);
int							set_desc_pc(t_data *data);
int							find_pc_pos(t_list *list, int *pc, int nb_champ,
		int value);
int							*set_array_pc(t_list *list_pc);
int							aff_window(t_data *data);
void						display_pc(t_data *data, int i, int *x_y,
		int champ_id);
void						clear_pc(t_data *data);
void						display_clear_pc(t_data *data, int i, int *x_y,
		int champ_id);
void						display_classique(t_data *data, int i, int *x_y,
		int champ_id);
void						init_infos_box(t_data *data);
int							set_live_infos(t_data *data);
t_display					*get_dsp_struct_addr(t_display *dsp);
void						print_str(t_data *data);
void						print_index(t_data *data, t_list *elem, int index);
void						clear_died_pc(t_data *data, t_list *elem);
void						print_pc(t_data *data);
void						delete_win(t_display *display);
void						sigkill(int code);

#endif
