/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_conf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:35:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/30 22:43:25 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		op_funcs_init(t_conf *conf)
{
	conf->op_inst[0] = c_live;
	conf->op_inst[1] = c_ld;
	conf->op_inst[2] = c_st;
	conf->op_inst[3] = c_add;
	conf->op_inst[4] = c_sub;
	conf->op_inst[5] = c_and;
	conf->op_inst[6] = c_or;
	conf->op_inst[7] = c_xor;
	conf->op_inst[8] = c_zjmp;
	conf->op_inst[9] = c_ldi;
	conf->op_inst[10] = c_sti;
	conf->op_inst[11] = c_fork;
	conf->op_inst[12] = c_lld;
	conf->op_inst[13] = c_lldi;
	conf->op_inst[14] = c_lfork;
	conf->op_inst[15] = c_aff;
}

void			ft_init_conf(int i, t_conf *conf)
{
	conf->dump = 0;
	conf->force_id = 0;
	conf->nb_players = 0;
	conf->nb_process = 0;
	conf->total_process = 0;
	conf->nb_live = 0;
	conf->last_live = 0;
	conf->nb_check = 0;
	conf->cycle = 0;
	conf->cycle_to_die = CYCLE_TO_DIE;
	conf->period = 0;
	conf->first_player = NULL;
	i = 0;
	while (i <= MAX_PLAYERS)
		conf->players[i++] = NULL;
	i = 0;
	while (i < MEM_SIZE)
		conf->grid[i++] = NULL;
	conf->op_tab = NULL;
	conf->first_process = NULL;
	op_funcs_init(conf);
}
