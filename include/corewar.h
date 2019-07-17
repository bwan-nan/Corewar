/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:48:51 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/17 17:32:58 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# define D_OPT_MAX 9
# define D_OP_MAX 17
# define D_MAN_PATH "./src/man/man_cor"

# include "ft_printf.h"
# include "op.h"

typedef struct			s_champ
{
	char				*path;
	int					fd;
	unsigned int		id;
	unsigned int		pc;
	unsigned int		magic;
	unsigned int		prog_size;
	unsigned int		nbr_live;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	char				inst[CHAMP_MAX_SIZE + 1];
	struct s_champ		*next;
}						t_champ;

typedef struct			s_cell
{
	unsigned char		val;
	unsigned char		pid;
}						t_cell;

typedef struct			s_process
{
	unsigned int		reg[REG_NUMBER];
	unsigned int		*pc;
	t_bool				carry;
	unsigned int		cycle_to_wait;
	
}						t_process;

typedef struct			s_conf
{
	int					opt[D_OPT_MAX];
	unsigned int		cycle;
	unsigned int		cycle_to_die;
	unsigned int		nbr_live;
	unsigned int		nbr_check;
	t_champ				*first_player;
	t_champ				*players[MAX_PLAYERS];
	t_cell				*grid[MEM_SIZE];
	t_process			*first_process;
	t_process			*last_process;
	const t_op			*op_tab;
}						t_conf;


void					ft_init_op(t_conf *conf);
void					ft_test_atoi_base(void);
int						ft_end(int error, t_conf *conf);
void					ft_clean(t_conf *conf);

#endif
