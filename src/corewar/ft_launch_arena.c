/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/19 12:07:52 by fdagbert         ###   ########.fr       */
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

static void		ft_print_arena(t_conf *conf)
{
	ft_printf("{YEL}Cycle:%u nb_process:%u, cycle_to_die:%u nb_live:%u nb_check:%u last_live:%d{OFF}\n\n", conf->cycle, conf->nb_process, conf->cycle_to_die, conf->nb_live, conf->nb_check, conf->last_live);
	ft_print_process(conf->first_process, conf->first_player, conf);
	ft_print_grid(conf);
}

static int		ft_check_args_size(unsigned int pc, unsigned char *ocp, unsigned char *args, t_conf *conf)
{
	int		i;
	int		args_size;
	t_ocp	ocp_split;

	i = 0;
	args_size = 1;
	if (pc < D_OP_MAX && conf->op_tab[pc].ocp)
	{
		args_size++;
		pc++;
		*ocp = conf->grid[pc]->val;
		ft_printf("OCP :%b\n", *ocp);
		*ocp = *ocp & 0xFF;
		ocp_split.arg1 = *ocp >> 6;
		*ocp = *ocp & 0x3F;
		ocp_split.arg2 = *ocp >> 4;
		*ocp = *ocp & 0x0F;
		ocp_split.arg3 = *ocp >> 2;
		*ocp = *ocp & 0x03;
		ocp_split.arg4 = *ocp;
		ft_printf("OCP SPLIT:%x %x %x %x\n", ocp_split.arg1, ocp_split.arg2, ocp_split.arg3, ocp_split.arg4);
		pc++;
		while (i < 4)
		{
			if (ocp_split.arg1 == 1)
			{
				args_size++;
				ft_memcpy(&args[i], &conf->grid[pc]->val, 1);
			}
			else if (ocp_split.arg1 == 2)
			{
				args_size += 2;
				ft_memcpy(&args[i], &conf->grid[pc]->val, 1);
				args[i] = args[i] << 8;
				pc++;
				ft_memcpy(&args[i], &conf->grid[pc]->val, 1);
			}
			else if (ocp_split.arg1 == 3)
			{
				args_size += 4;
				//T_IND == 2 || T_IND == 4
				ft_memcpy(&args[i], &conf->grid[pc]->val, 1);
				args[i] = args[i] << 8;
				pc++;
				ft_memcpy(&args[i], &conf->grid[pc]->val, 1);
				args[i] = args[i] << 8;
				pc++;
				ft_memcpy(&args[i], &conf->grid[pc]->val, 1);
				args[i] = args[i] << 8;
				pc++;
				ft_memcpy(&args[i], &conf->grid[pc]->val, 1);
				args[i] = args[i] << 8;
				pc++;
			}
			i++;
		}
	}
	else if (pc < D_OP_MAX)
		return (T_DIR + 1);
	else
		return (1);
	return (args_size);
}

static void		ft_purge_process(t_process *process, t_conf *conf)
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
			free(process);
			process = next;
		}
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
	int		down;

	down = 0;
	if (conf->nb_live >= NBR_LIVE)
		down++;
	else if (conf->nb_check >= MAX_CHECKS)
		down++;
	else
		conf->nb_check++;
	if (down)
	{
		ft_purge_process(conf->first_process, conf);
		conf->cycle_to_die -= CYCLE_DELTA;
	}
}

int				ft_launch_arena(t_process *process, t_conf *conf)
{
	unsigned char	op_code;
	unsigned char	ocp;
	unsigned char	args_size;
	unsigned char	args[4];

	op_code = 0;
	ocp = 0;
	args[0] = 0;
	args[1] = 0;
	args[2] = 0;
	args[3] = 0;
	args_size = 0;
	while (conf->nb_process)
	{
		process = conf->first_process;
		while (process)
		{
			process->cycle_to_wait--;
			if (!process->cycle_to_wait)
			{
				op_code = conf->grid[process->pc]->val;
				args_size = ft_check_args_size(process->pc, &ocp, &args[0], conf);
				process->pc = (process->pc + args_size) % MEM_SIZE;
				ft_printf("process %u new pc:%u\n", process->id_proc, process->pc);
				//op_funcs[op_code](conf->grid[process->pc]->pid, ocp, args, conf);
				op_code = conf->grid[process->pc]->val;
				process->cycle_to_wait = conf->op_tab[op_code].cycles;
			}
			process = process->next;
		}
		ft_check_cycle_to_die(conf);
		if (conf->opt[8])
			ft_print_arena(conf);
		conf->cycle++;
	}
	return (0);
}
