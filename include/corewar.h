/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:48:51 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/23 18:47:57 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# define D_OPT_MAX			10
# define D_OP_MAX			16
# define D_DEBUG_SIZE		64
# define D_MAN_PATH			"./src/man/man_cor"
# define D_HEAD_SIZE		16 + PROG_NAME_LENGTH + COMMENT_LENGTH
# define D_BIN_MAX_SIZE		CHAMP_MAX_SIZE + D_HEAD_SIZE

# include "ft_printf.h"
# include "op.h"

typedef struct			s_champ
{
	char				*path;
	int					fd;
	unsigned int		id;
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
	unsigned int		val;
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
	unsigned int		pc;
	unsigned int		cycle_to_wait;
	t_bool				carry;
	unsigned char		op_code;
	unsigned char		ocp;
	unsigned char		fct_args[4];
	unsigned int		args_size;
	t_ocp				ocp_split;
	struct s_process	*next;
}						t_process;

typedef struct			s_conf
{
	int					opt[D_OPT_MAX + 1];
	unsigned int		dump;
	unsigned int		nb_player;
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
	void				(*op_funcs[16]) (unsigned int pid, t_ocp ocp, int args[4], struct s_conf *conf); //added
}						t_conf;

void					c_live(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_ld(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_st(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_add(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_sub(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_and(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_or(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_xor(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_zjump(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_ldi(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_sti(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_fork(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_lld(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_lldi(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_lfork(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added
void					c_aff(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf); //added

void					ft_init_op(t_conf *conf);
void					ft_init_op(t_conf *conf);
int						ft_champion_parser(t_champ *champ, t_conf *conf);
int						ft_init_arena(t_champ *champ, t_conf *conf);
int						ft_launch_arena(t_process *process, t_conf *conf);
int						ft_end(int error, t_conf *conf);
void					ft_clean(t_conf *conf);

#endif
