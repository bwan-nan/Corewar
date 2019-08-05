/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/05 06:55:12 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_reinit_process(t_process *process)
{
	process->ocp = 0;
	process->fct_args[0] = 0;
	process->fct_args[1] = 0;
	process->fct_args[2] = 0;
	process->fct_args[3] = 0;
	process->args_size = 0;
	process->ocp_splitted.arg1 = 0;
	process->ocp_splitted.arg2 = 0;
	process->ocp_splitted.arg3 = 0;
	process->ocp_splitted.arg4 = 0;
}

static void		ft_init_process_next(t_process *process, t_conf *conf)
{
	int		i;

	i = 0;
	if (process->op_code < D_OP_MAX)
	{
		process->cycle_to_wait = conf->op_tab[process->op_code].cycles;
		if (conf->op_tab[process->op_code].ocp)
			process->ocp = conf->grid[(process->pc + 1) % MEM_SIZE]->val;
	}
	else
		process->op_code = UCHAR_MAX;
	while (i < 4)
		process->fct_args[i++] = 0;
	process->args_size = 0;
	process->ocp_splitted.arg1 = 0;
	process->ocp_splitted.arg2 = 0;
	process->ocp_splitted.arg3 = 0;
	process->ocp_splitted.arg4 = 0;
	conf->grid[process->pc]->pc = process->id_champ;
	conf->grid[process->pc]->nb_pc++;
}

void			ft_init_process(int reinit, t_process *process, t_champ *champ,
		t_conf *conf)
{
	int i;

	i = 1;
	if (reinit)
		ft_reinit_process(process);
	else
	{
		conf->nb_process++;
		conf->total_process++;
		champ->nb_process++;
		process->id_proc = conf->total_process;
		process->id_champ = champ->id;
		process->nb_live = 0;
		process->reg[0] = -(champ->id);
		while (i < REG_NUMBER)
			process->reg[i++] = 0;
		process->pc = champ->init_pc;
		process->carry = 0;
		process->op_code = conf->grid[process->pc]->val - 1;
		process->cycle_to_wait = 1;
		process->ocp = 0;
		ft_init_process_next(process, conf);
	}
}
