/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_visu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 02:25:49 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/04 03:35:47 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_print_process(t_process *process, t_conf *conf)
{
	if (conf->opt[1])
	{
		ft_printf("Debug process, id_proc:{CYA}%5u{OFF} id_champ:{CYA}%2u{OFF} \
				nb_live:{CYA}%4u{OFF} pc:{CYA}%4d{OFF} cycle_wait:{CYA}%4u{OFF}\
				carry:{CYA}%u{OFF} ",
				process->id_proc, process->id_champ, process->nb_live,
				process->pc, process->cycle_to_wait, process->carry);
		if (process->op_code < D_OP_MAX)
			ft_printf("inst:{CYA}%5s{OFF} ",
					conf->op_tab[process->op_code].name);
		ft_printf("op_code:{CYA}%2u{OFF} ocp:{CYA}%.2X{OFF} args_size:{CYA}%2u\
				{OFF} fct_args[0]:{CYA}%.2X{OFF} fct_args[1]:{CYA}%.2X{OFF} \
				fct_args[2]:{CYA}%.2X{OFF} fct_args[3]:{CYA}%.2X{OFF}\n",
				process->op_code + 1, process->ocp, process->args_size,
				process->fct_args[0], process->fct_args[1],
				process->fct_args[2], process->fct_args[3]);
	}
}

static void		ft_print_all_process(t_process *process, t_conf *conf)
{
	unsigned int		i;

	ft_printf("\n");
	while (process)
	{
		i = -1;
		ft_print_process(process, conf);
		while (++i < REG_NUMBER)
		{
			if (i == 8)
				ft_printf("|\n");
			ft_printf("| Reg[%2d]:{MAG}%8X{OFF} ", i, process->reg[i]);
		}
		ft_printf("|\n");
		process = process->next;
	}
	ft_printf("\n");
	i = 1;
	while (i <= conf->nb_players)
	{
		if (conf->players[i])
			ft_printf("Player %u, nb_process:%u nb_live:%u\n", i,
					conf->players[i]->nb_process, conf->players[i]->nb_live);
		i++;
	}
}

static void		ft_print_arena(t_conf *conf)
{
	if (conf->opt[1])
	{
		ft_print_all_process(conf->first_process, conf);
		ft_printf("{YEL}Conf, total_process:%u nb_process:%u \
				cycle_to_die:%u nb_live:%u nb_check:%u last_live:%d period: %u{OFF}\n",
				conf->total_process, conf->nb_process, conf->cycle_to_die,
				conf->nb_live, conf->nb_check, conf->last_live, conf->period);
	}
	if (conf->opt[8])
		ft_print_grid(conf);
}

static void		ft_init_visu(t_conf *conf)
{
	if (conf->opt[8] && conf->opt[10])
		ft_printf("{CLEAR}");
	if (conf->opt[8] && !conf->opt[0])
		ft_print_arena(conf);
}

void			ft_print_visu(int step, t_process *process, t_conf *conf)
{
	if (!step)
		ft_init_visu(conf);
	else if (step == 1 && !conf->opt[3] && conf->opt[1])
		ft_printf("{YEL}\nCycle:%u{OFF}\n", conf->cycle);
	else if (step == 2)
	{
		if (conf->opt[1])
		{
			ft_printf("Process %u from player %u executed.\n",
					process->id_proc, process->id_champ);
			ft_print_process(process, conf);
		}
	}
	else if (step == 3)
	{
		if (conf->opt[3] && conf->opt[9])
			ft_print_xml(conf);
	}
	else if (step == 4)
	{
		if (conf->opt[3] && !conf->opt[9])
			ft_print_xml(conf);
		ft_print_arena(conf);
	}
	else if (step == 5)
	{
		ft_print_grid(conf);
		if (conf->opt[3])
			ft_printf("<end_reached/>\n");
	}
}
