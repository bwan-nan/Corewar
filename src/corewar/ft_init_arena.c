/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/19 12:08:53 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*static void		ft_print_grid(t_conf *conf)
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
}*/

static void		ft_print_process(t_process *process, t_champ *champ, t_conf *conf)
{
	int		i;

	i = -1;
	ft_printf("New process, id_proc:%u, id_champ:%u, pc:%d, cycle_wait:%u, carry:%ld\n",
			process->id_proc, process->id_champ, process->pc, process->cycle_to_wait, process->carry);
	while (++i < REG_NUMBER)
		ft_printf("Reg[%d]:%d |  ", i, process->reg[i]);
	ft_printf("\nConf nb_process:%u total_process:%u champ_process:%u\n\n",
			conf->nb_process, conf->total_process, champ->nb_process);
}

static void		ft_init_process(t_process *process, t_champ *champ, t_conf *conf)
{
	int		i;

	i = 1;
	conf->nb_process++;
	conf->total_process++;
	champ->nb_process++;
	process->id_proc = conf->total_process;
	process->id_champ = champ->id;
	process->nb_live = 0;
	process->reg[0] = champ->id;
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
	process->pc = champ->init_pc;
	i = conf->grid[process->pc]->val;
	process->cycle_to_wait = conf->op_tab[i].cycles;
	process->carry = 0;
	process->next = NULL;
}


static int		ft_create_process(t_process *process, t_champ *champ, t_conf *conf)
{
	while (champ)
	{
		if (!process)
		{
			if (!(process = (t_process *)malloc(sizeof(*process))))
				return (-1);
			conf->first_process = process;
			conf->last_process = process;
		}
		else
		{
			if (!(process->next = (t_process *)malloc(sizeof(*process))))
				return (-1);
			process = process->next;
			conf->last_process = process;
		}
		ft_init_process(process, champ, conf);
		if (conf->opt[8])
			ft_print_process(process, champ, conf);
		process = conf->last_process;
		champ = champ->next;
	}
	return (0);
}

int				ft_init_arena(t_champ *champ, t_conf *conf)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < MEM_SIZE)
	{
		if (!(conf->grid[i] = (t_cell *)malloc(sizeof(*conf->grid[i]))))
			return (-1);
		conf->grid[i]->val = 0;
		conf->grid[i]->pid = -1;
		i++;
	}
	while (champ)
	{
		i = champ->init_pc;
		j = 0;
		while (j < champ->inst_size)
		{
			conf->grid[i]->val = champ->inst[j];
			conf->grid[i]->pid = champ->id;
			i++;
			j++;
		}
		champ = champ->next;
	}
	if (ft_create_process(conf->first_process, conf->first_player, conf) < 0)
		return (-1);
	//if (conf->opt[8])
	//	ft_print_grid(conf);
	return (0);
}
