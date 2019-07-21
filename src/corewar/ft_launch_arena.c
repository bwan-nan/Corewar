/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/22 01:32:23 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_print_grid(t_conf *conf)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (conf->grid[i]->pid == 0)
			ft_printf("| {GRE}%.2X{OFF} ", conf->grid[i]->val);
		else if (conf->grid[i]->pid == 1)
			ft_printf("| {CYA}%.2X{OFF} ", conf->grid[i]->val);
		else if (conf->grid[i]->pid == 2)
			ft_printf("| {MAG}%.2X{OFF} ", conf->grid[i]->val);
		else if (conf->grid[i]->pid == 3)
			ft_printf("| {RED}%.2X{OFF} ", conf->grid[i]->val);
		else
			ft_printf("| %.2X ", conf->grid[i]->val);
		i++;
		if (!(i % D_DEBUG_SIZE))
			ft_printf("|\n");
	}
	ft_printf("\n");
}

static void		ft_print_process(t_process *process, t_champ *champ, t_conf *conf)
{
	int		i;

	while (process)
	{
		i = -1;
		ft_printf("Debug process, id_proc:%u, id_champ:%u, pc:%d, cycle_wait:%u, carry:%ld\n",
				process->id_proc, process->id_champ, process->pc, process->cycle_to_wait, process->carry);
		while (++i < REG_NUMBER)
			ft_printf("Reg[%d]:%d |  ", i, process->reg[i]);
		ft_printf("\nConf nb_process:%u total_process:%u champ_process:%u\n\n",
				conf->nb_process, conf->total_process, champ->nb_process);
		process = process->next;
	}
}

static void			ft_print_arena(t_conf *conf)
{
	ft_printf("{YEL}Cycle:%u nb_process:%u, cycle_to_die:%u nb_live:%u nb_check:%u last_live:%d{OFF}\n\n", conf->cycle, conf->nb_process, conf->cycle_to_die, conf->nb_live, conf->nb_check, conf->last_live);
	ft_print_process(conf->first_process, conf->first_player, conf);
	ft_print_grid(conf);
}

static int			ft_check_op_code(unsigned int pc, t_conf *conf)
{
	if (conf->op_code < D_OP_MAX)
	{	
		if (conf->op_tab[conf->op_code].ocp)
			conf->ocp = conf->grid[pc + 1]->val;
		return (0);
	}
	else
		return (-16);
}

static int				ft_check_ocp_split(int i, int pc, char ocp_split_arg, t_conf *conf)
{
	if (ocp_split_arg == 0)
		return (pc);
	else if (ocp_split_arg == 1)
	{
		conf->args_size++;
		ft_memcpy(&conf->fct_args[i], &conf->grid[pc]->val, 1);
		pc++;
	}
	else if (ocp_split_arg == 2)
	{
		//T_DIR == 2 || T_DIR == 4
		conf->args_size += conf->op_tab[conf->op_code].dir_size;
		ft_memcpy(&conf->fct_args[i], &conf->grid[pc]->val, 1);
		conf->fct_args[i] = conf->fct_args[i] << 8;
		pc++;
		ft_memcpy(&conf->fct_args[i], &conf->grid[pc]->val, 1);
		pc++;
		if (conf->op_tab[conf->op_code].dir_size == 4)
		{
			conf->fct_args[i] = conf->fct_args[i] << 8;
			ft_memcpy(&conf->fct_args[i], &conf->grid[pc]->val, 1);
			conf->fct_args[i] = conf->fct_args[i] << 8;
			pc++;
			ft_memcpy(&conf->fct_args[i], &conf->grid[pc]->val, 1);
			pc++;
		}
	}
	else if (ocp_split_arg == 3)
	{
		conf->args_size += 2;
		ft_memcpy(&conf->fct_args[i], &conf->grid[pc]->val, 1);
		conf->fct_args[i] = conf->fct_args[i] << 8;
		pc++;
		ft_memcpy(&conf->fct_args[i], &conf->grid[pc]->val, 1);
		pc++;
	}
	else
		return (-17);
	return (pc);
}

static int				ft_check_args_size(int pc, t_conf *conf)
{
	t_ocp			ocp_split;

	conf->args_size = 1;
	ocp_split.arg1 = 0;
	ocp_split.arg2 = 0;
	ocp_split.arg3 = 0;
	ocp_split.arg4 = 0;
	if (conf->op_tab[conf->op_code].ocp)
	{
		conf->args_size++;
		pc++;
		conf->ocp = conf->grid[pc]->val;
		ft_printf("OCP :%b\n", conf->ocp);
		conf->ocp = conf->ocp & 0xFF;
		ocp_split.arg1 = conf->ocp >> 6;
		conf->ocp = conf->ocp & 0x3F;
		ocp_split.arg2 = conf->ocp >> 4;
		conf->ocp = conf->ocp & 0x0F;
		ocp_split.arg3 = conf->ocp >> 2;
		conf->ocp = conf->ocp & 0x03;
		ocp_split.arg4 = conf->ocp;
		ft_printf("OCP SPLIT:%x %x %x %x\n", ocp_split.arg1, ocp_split.arg2, ocp_split.arg3, ocp_split.arg4);
		pc++;
		if ((pc = ft_check_ocp_split(0, pc, ocp_split.arg1, conf)) < 0)
			return (-17);
		if ((pc = ft_check_ocp_split(1, pc, ocp_split.arg2, conf)) < 0)
			return (-17);
		if ((pc = ft_check_ocp_split(2, pc, ocp_split.arg3, conf)) < 0)
			return (-17);
		if ((pc = ft_check_ocp_split(3, pc, ocp_split.arg4, conf)) < 0)
			return (-17);
		ft_printf("PC:%u\n", pc);
	}
	else
		conf->args_size = conf->op_tab[conf->op_code].dir_size + 1;
	return (0);
}

static void			ft_init_fct_args(t_conf *conf)
{
	conf->args_size = 0;
	conf->op_code = 0;
	conf->ocp = 0;
	conf->fct_args[0] = 0;
	conf->fct_args[1] = 0;
	conf->fct_args[2] = 0;
	conf->fct_args[3] = 0;
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
			conf->players[process->id_champ]->nb_process--;
			conf->nb_process--;
			ft_printf("Le processus %u créé par %u a été mis à mort !\n", process->id_proc, process->id_champ);
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
	if (conf->opt[8])
		ft_print_arena(conf);
	while (conf->nb_process)
	{
		conf->cycle++;
		conf->period++;
		process = conf->first_process;
		while (process)
		{
			ft_init_fct_args(conf);
			process->cycle_to_wait--;
			if (!process->cycle_to_wait)
			{
				ft_printf("cycle:%u process:%u player:%u pc:%u ", conf->cycle, process->id_proc, process->id_champ, process->pc);
				conf->op_code = conf->grid[process->pc]->val - 1;
				ft_printf("op_code:%u ", conf->op_code + 1);
				if (ft_check_op_code(process->pc, conf) < 0)
					return (-16);
				ft_printf("ocp:%x\n", conf->ocp);
				if (ft_check_args_size(process->pc, conf) < 0)
					return (-17);
				ft_printf("args_size:%u fct_args[0]:%x fct_args[1]:%x fct_args[2]:%x fct_args[3]:%x\n", conf->args_size, conf->fct_args[0], conf->fct_args[1], conf->fct_args[2], conf->fct_args[3]);
				//op_funcs[op_code](conf->grid[process->pc]->pid, conf->ocp, conf->fct_args, conf);
				process->pc = process->pc + conf->args_size % (MEM_SIZE - 1);
				conf->op_code = conf->grid[process->pc]->val - 1;
				if (ft_check_op_code(process->pc, conf) < 0)
					return (-16);
				process->cycle_to_wait = conf->op_tab[conf->op_code].cycles;
				ft_printf("process:%u player:%u new pc:%u new op_code:%u, new cycle_wait:%u\n\n", process->id_proc, process->id_champ, process->pc, conf->op_code + 1, process->cycle_to_wait);
			}
			process = process->next;
		}
		if (conf->period == conf->cycle_to_die)
			ft_check_cycle_to_die(conf);
		if (conf->opt[8])
			ft_print_arena(conf);
	}
	return (0);
}
