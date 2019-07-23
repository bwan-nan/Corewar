/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/23 02:26:23 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_print_grid(t_conf *conf)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (conf->grid[i]->pc == -1)
		{
			if (conf->grid[i]->pid == 1)
				ft_printf("| {GRE}%.2X{OFF} ", conf->grid[i]->val);
			else if (conf->grid[i]->pid == 2)
				ft_printf("| {CYA}%.2X{OFF} ", conf->grid[i]->val);
			else if (conf->grid[i]->pid == 3)
				ft_printf("| {MAG}%.2X{OFF} ", conf->grid[i]->val);
			else if (conf->grid[i]->pid == 4)
				ft_printf("| {RED}%.2X{OFF} ", conf->grid[i]->val);
			else
				ft_printf("| %.2X ", conf->grid[i]->val);
		}
		else
		{
			if (conf->grid[i]->pc == 1)
				ft_printf("| {INVER}{GRE}%.2X{OFF} ", conf->grid[i]->val);
			else if (conf->grid[i]->pc == 2)
				ft_printf("| {INVER}{CYA}%.2X{OFF} ", conf->grid[i]->val);
			else if (conf->grid[i]->pc == 3)
				ft_printf("| {INVER}{MAG}%.2X{OFF} ", conf->grid[i]->val);
			else if (conf->grid[i]->pc == 4)
				ft_printf("| {INVER}{RED}%.2X{OFF} ", conf->grid[i]->val);
			else
				ft_printf("| {INVER}%.2X{OFF} ", conf->grid[i]->val);
		}
		i++;
		if (!(i % D_DEBUG_SIZE))
			ft_printf("|\n");
	}
	ft_printf("\n");
}

static void		ft_print_process(t_process *process, t_conf *conf)
{
	if (conf->opt[1] || (conf->opt[0] && conf->cycle == conf->dump))
	{
		ft_printf("Debug process, id_proc:{CYA}%4u{OFF} id_champ:{CYA}%2u{OFF}",
				process->id_proc, process->id_champ);
		ft_printf(" nb_live:{CYA}%3u{OFF} pc:{CYA}%4d{OFF} ",
				process->nb_live, process->pc);
		ft_printf("cycle_wait:{CYA}%4u{OFF} carry:{CYA}%2ld{OFF} ",
				process->cycle_to_wait, process->carry);
		if (process->op_code < D_OP_MAX)
			ft_printf("inst:{CYA}%5s{OFF} ",
					conf->op_tab[process->op_code].name);
		ft_printf("op_code:{CYA}%2u{OFF} ocp:{CYA}%.2X{OFF} args_size:{CYA}%2u",
				process->op_code + 1, process->ocp, process->args_size);
		ft_printf("{OFF} fct_args[0]:{CYA}%.2X{OFF} fct_args[1]:{CYA}%.2X{OFF}",
				process->fct_args[0], process->fct_args[1]);
		ft_printf(" fct_args[2]:{CYA}%.2X{OFF} fct_args[3]:{CYA}%.2X{OFF}\n",
				process->fct_args[2], process->fct_args[3]);
	}
}

static void		ft_print_all_process(t_process *process, t_conf *conf)
{
	int					i;

	while (process)
	{
		i = -1;
		ft_print_process(process, conf);
		while (++i < REG_NUMBER)
			ft_printf("| Reg[%d]:{MAG}%.2X{OFF} ", i, process->reg[i]);
		ft_printf("|\n");
		process = process->next;
	}
	ft_printf("\n");
	i = 1;
	while (i <= (int)conf->nb_player)
	{
		if (conf->players[i])
			ft_printf("Player %u, nb_process:%u\n", i,
					conf->players[i]->nb_process);
		i++;
	}
}

static void			ft_print_arena(t_conf *conf)
{
	if ((conf->opt[0] && conf->cycle == conf->dump) || conf->opt[1])
	{
		ft_print_all_process(conf->first_process, conf);
		ft_printf("{YEL}Conf, total_process:%u nb_process:%u cycle_to_die:%u ",
				conf->total_process, conf->nb_process, conf->cycle_to_die);
		ft_printf("nb_live:%u nb_check:%u last_live:%d{OFF}\n",
				conf->nb_live, conf->nb_check, conf->last_live);
	}
	if ((conf->opt[0] && conf->cycle == conf->dump) || conf->opt[8])
		ft_print_grid(conf);
}

static int			ft_check_op_code(t_process *process, t_conf *conf)
{
	unsigned int	pc;

	pc = process->pc;
	if (process->op_code < D_OP_MAX)
	{	
		if (conf->op_tab[process->op_code].ocp)
			process->ocp = conf->grid[pc + 1]->val;
		return (0);
	}
	else if (process->op_code == UCHAR_MAX)
		return (0);
	else
		return (-16);
}

static int				ft_check_ocp_split(int i, char ocp_split_arg, t_process *process, t_conf *conf)
{
	unsigned char	pc;

	pc = process->pc;
	if (ocp_split_arg == 0)
		return (pc);
	else if (ocp_split_arg == 1)
	{
		process->args_size++;
		ft_memcpy(&process->fct_args[i], &conf->grid[pc]->val, 1);
		pc++;
	}
	else if (ocp_split_arg == 2)
	{
		//T_DIR == 2 || T_DIR == 4
		process->args_size += conf->op_tab[process->op_code].dir_size;
		ft_memcpy(&process->fct_args[i], &conf->grid[pc]->val, 1);
		process->fct_args[i] = process->fct_args[i] << 8;
		pc++;
		ft_memcpy(&process->fct_args[i], &conf->grid[pc]->val, 1);
		pc++;
		if (conf->op_tab[process->op_code].dir_size == 4)
		{
			process->fct_args[i] = process->fct_args[i] << 8;
			ft_memcpy(&process->fct_args[i], &conf->grid[pc]->val, 1);
			process->fct_args[i] = process->fct_args[i] << 8;
			pc++;
			ft_memcpy(&process->fct_args[i], &conf->grid[pc]->val, 1);
			pc++;
		}
	}
	else if (ocp_split_arg == 3)
	{
		process->args_size += 2;
		ft_memcpy(&process->fct_args[i], &conf->grid[pc]->val, 1);
		process->fct_args[i] = process->fct_args[i] << 8;
		pc++;
		ft_memcpy(&process->fct_args[i], &conf->grid[pc]->val, 1);
		pc++;
	}
	else
		return (-17);
	return (pc);
}

static int				ft_check_args_size(t_process *process, t_conf *conf)
{
	int			pc;
	t_ocp		ocp_split;

	pc = (int)process->pc;
	process->args_size = 1;
	ocp_split.arg1 = 0;
	ocp_split.arg2 = 0;
	ocp_split.arg3 = 0;
	ocp_split.arg4 = 0;
	if (conf->op_tab[process->op_code].ocp)
	{
		process->args_size++;
		pc++;
		process->ocp = conf->grid[pc]->val;
		//ft_printf("OCP :%b\n", process->ocp);
		process->ocp = process->ocp & 0xFF;
		ocp_split.arg1 = process->ocp >> 6;
		process->ocp = process->ocp & 0x3F;
		ocp_split.arg2 = process->ocp >> 4;
		process->ocp = process->ocp & 0x0F;
		ocp_split.arg3 = process->ocp >> 2;
		process->ocp = process->ocp & 0x03;
		ocp_split.arg4 = process->ocp;
		//ft_printf("OCP SPLIT:%x %x %x %x\n", ocp_split.arg1, ocp_split.arg2, ocp_split.arg3, ocp_split.arg4);
		pc++;
		if ((pc = ft_check_ocp_split(0, ocp_split.arg1, process, conf)) < 0)
			return (-17);
		if ((pc = ft_check_ocp_split(1, ocp_split.arg2, process, conf)) < 0)
			return (-17);
		if ((pc = ft_check_ocp_split(2, ocp_split.arg3, process, conf)) < 0)
			return (-17);
		if ((pc = ft_check_ocp_split(3, ocp_split.arg4, process, conf)) < 0)
			return (-17);
	}
	else
		process->args_size = conf->op_tab[process->op_code].dir_size + 1;
	return (0);
}

static void			ft_reinit_process(t_process *process, t_conf *conf)
{
	process->op_code = conf->grid[process->pc]->val - 1;
	process->ocp = 0;
	process->fct_args[0] = 0;
	process->fct_args[1] = 0;
	process->fct_args[2] = 0;
	process->fct_args[3] = 0;
	process->args_size = 0;
}

static void			ft_purge_process(t_process *process, t_conf *conf)
{
	t_process		*last;
	t_process		*next;

	last = process;
	next = process->next;
	while (process)
	{
		if (!process->nb_live)
		{
			if (process == conf->first_process)
				conf->first_process = next;
			else
				last->next = next;
			conf->grid[process->pc]->pc = -1;
			conf->players[process->id_champ]->nb_process--;
			conf->nb_process--;
			if (conf->opt[1])
				ft_printf("Le processus %u créé par le joueur %u a été mis à mort !\n", process->id_proc, process->id_champ);
			free(process);
			process = next;
		}
		else
			process->nb_live = 0;
		last = process;
		process = next;
		if (process)
			next = process->next;
		else
			next = NULL;
	}
}

static void		ft_check_cycle_to_die(t_conf *conf)
{

	conf->period = 0;
	ft_purge_process(conf->first_process, conf);
	if (conf->nb_live >= NBR_LIVE || conf->nb_check == MAX_CHECKS)
	{
		conf->cycle_to_die -= CYCLE_DELTA;
		conf->nb_live = 0;
		conf->nb_check = 0;
	}
	else
		conf->nb_check++;
}

int				ft_launch_arena(t_process *process, t_conf *conf)
{
	if (conf->opt[8] && !conf->opt[0])
		ft_print_arena(conf);
	while (conf->nb_process && (!conf->opt[0] || conf->cycle <= conf->dump))
	{
		conf->cycle++;
		conf->period++;
		if (conf->opt[1] || (conf->opt[0] && conf->cycle == conf->dump))
			ft_printf("{YEL}\nCycle:%u{OFF}\n", conf->cycle);
		process = conf->first_process;
		while (process)
		{
			process->cycle_to_wait--;
			if (!process->cycle_to_wait)
			{
				ft_reinit_process(process, conf);
				if (ft_check_op_code(process, conf) < 0)
					return (-16);
				conf->grid[process->pc]->pc = -1;
				if (process->op_code == UCHAR_MAX)
					process->pc = (process->pc + 1) % (MEM_SIZE - 1);
				else
				{
					if (ft_check_args_size(process, conf) < 0)
						return (-17);
					if (conf->opt[1])
						ft_printf("Process %u from player %u executed.\n",
								process->id_proc, process->id_champ);
					ft_print_process(process, conf);
					//op_funcs[op_code](conf->grid[process->pc]->pid, process->ocp, process->fct_args, conf);
					process->pc = (process->pc + process->args_size) % (MEM_SIZE - 1);
				}
				conf->grid[process->pc]->pc = process->id_champ;
				ft_reinit_process(process, conf);
				if (ft_check_op_code(process, conf) < 0)
					return (-16);
				if (process->op_code == UCHAR_MAX)
					process->cycle_to_wait = 1;
				else
					process->cycle_to_wait = conf->op_tab[process->op_code].cycles;
				if ((conf->opt[1]) || (conf->opt[0] && conf->cycle == conf->dump))
				{
					ft_printf("Process updated, pc:{CYA}%4u{OFF}", process->pc);
					ft_printf(" op_code:{CYA}%2u{OFF} cycle_wait:{CYA}%4u{OFF}",
							process->op_code + 1, process->cycle_to_wait);
					ft_printf("\n\n");
				}
			}
			process = process->next;
		}
		if (conf->period == conf->cycle_to_die)
			ft_check_cycle_to_die(conf);
		ft_print_arena(conf);
	}
	return (0);
}
