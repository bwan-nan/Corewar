/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/23 02:24:31 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_init_process(t_process *process, t_champ *champ, t_conf *conf)
{
	int		i;

	conf->nb_process++;
	conf->total_process++;
	champ->nb_process++;
	process->id_proc = conf->total_process;
	process->id_champ = champ->id;
	process->nb_live = 0;
	process->reg[0] = champ->id;
	i = 1;
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
	process->pc = champ->init_pc;
	process->carry = 0;
	process->op_code = conf->grid[process->pc]->val - 1;
	process->cycle_to_wait = conf->op_tab[process->op_code].cycles;
	process->ocp = 0;
	i = 0;
	while (i < 4)
		process->fct_args[i++] = 0;
	process->args_size = 0;
	conf->grid[process->pc]->pc = process->id_champ;
}


static int		ft_create_process(t_process *process, t_champ *champ, t_conf *conf)
{
	while (champ)
	{
		if (!(process = (t_process *)malloc(sizeof(*process))))
			return (-1);
		process->next = conf->first_process;
		conf->first_process = process;
		ft_init_process(process, champ, conf);
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
		conf->grid[i]->pc = -1;
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
	return (0);
}
