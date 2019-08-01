/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:48:51 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/01 14:14:34 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# define D_OPT_MAX			11
# define D_OP_MAX			16
# define D_CLEAR_TRICK		0
# define D_GRID_SIZE		64
# define D_MAN_PATH			"./src/man/man_cor"
# define D_HEAD_SIZE		16 + PROG_NAME_LENGTH + COMMENT_LENGTH
# define D_BIN_MAX_SIZE		CHAMP_MAX_SIZE + D_HEAD_SIZE

# include "ft_printf.h"
# include "op.h"

typedef struct			s_champ
{
	char				*path;
	int					fd;
	int					id;
	int					force_id;
	unsigned int		nb_live;
	unsigned int		nb_process;
	unsigned int		init_pc;
	unsigned int		inst_size;
	unsigned int		magic;
	unsigned int		padding1;
	unsigned int		padding2;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		inst[CHAMP_MAX_SIZE + 1];
	struct s_champ		*next;
}						t_champ;

typedef struct			s_cell
{
	unsigned char		val;
	unsigned int		pid;
	unsigned int		pc;
}						t_cell;

typedef struct			s_ocp
{
	char				arg1;
	char				arg2;
	char				arg3;
	char				arg4;
}						t_ocp;

typedef struct			s_process
{
	unsigned int		id_proc;
	unsigned int		id_champ;
	unsigned int		nb_live;
	unsigned int		reg[REG_NUMBER];
	int					pc;
	unsigned int		cycle_to_wait;
	t_bool				carry;
	unsigned char		op_code;
	unsigned char		ocp;
	unsigned int		args_size;
	int					fct_args[4];
	t_ocp				ocp_splitted;
	struct s_process	*next;
}						t_process;

typedef struct			s_conf
{
	int					opt[D_OPT_MAX + 1];
	unsigned int		dump;
	unsigned int		force_id;
	unsigned int		check_id;
	unsigned int		nb_players;
	unsigned int		nb_process;
	unsigned int		total_process;
	unsigned int		nb_live;
	unsigned int		last_live;
	unsigned int		nb_check;
	unsigned int		cycle;
	unsigned int		cycle_to_die;
	unsigned int		period;
	t_champ				*first_player;
	t_champ				*players[MAX_PLAYERS + 1];
	t_cell				*grid[MEM_SIZE];
	t_process			*first_process;
	const t_op			*op_tab;
	int					(*op_inst[D_OP_MAX])(t_process *process,
							struct s_conf *conf);
}						t_conf;

int						c_check_arg_type(int index1, int index2, int reg3,
							t_process *process);
int						c_modulo_indirect(int val, int pc, int index,
							t_conf *conf);
int						c_sum(int index1, int index2, t_process *process);
void					c_store_int(int pc, int reg1, t_process *process,
							t_conf *conf);
void					c_read_int(int pc, int reg1, t_process *process,
							t_conf *conf);

int						c_live(t_process *process, t_conf *conf);
int						c_ld(t_process *process, t_conf *conf);
int						c_st(t_process *process, t_conf *conf);
int						c_add(t_process *process, t_conf *conf);
int						c_sub(t_process *process, t_conf *conf);
int						c_and(t_process *process, t_conf *conf);
int						c_or(t_process *process, t_conf *conf);
int						c_xor(t_process *process, t_conf *conf);
int						c_zjmp(t_process *process, t_conf *conf);
int						c_ldi(t_process *process, t_conf *conf);
int						c_sti(t_process *process, t_conf *conf);
int						c_fork(t_process *process, t_conf *conf);
int						c_lld(t_process *process, t_conf *conf);
int						c_lldi(t_process *process, t_conf *conf);
int						c_lfork(t_process *process, t_conf *conf);
int						c_aff(t_process *process, t_conf *conf);

void					ft_init_conf(int i, t_conf *conf);
void					ft_init_op(t_conf *conf);
int						ft_end(int error, t_conf *conf);
int						ft_check_args(int argc, char **argv, const char *keys,
							t_conf *conf);
int						ft_check_players(char *argv, t_conf *conf);
int						ft_champion_parser(t_champ *champ, t_conf *conf);
int						ft_init_arena(int i, t_champ *champ, t_conf *conf);
int						ft_launch_arena(int ret, t_process *process,
							t_conf *conf);
int						ft_check_args_size(t_process *process, t_conf *conf);
void					ft_check_cycle_to_die(t_conf *conf);
void					ft_print_visu(int step, t_process *process,
							t_conf *conf);
void					ft_print_grid(t_conf *conf);
void					ft_print_xml(t_conf *conf);
void					ft_clean(t_conf *conf);

#endif
