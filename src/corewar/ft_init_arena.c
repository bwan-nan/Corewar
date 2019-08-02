/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/02 00:25:56 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_init_grid(t_champ *champ, t_conf *conf)
{
	unsigned int	i;
	unsigned int	j;

	i = champ->init_pc;
	j = 0;
	while (j < champ->inst_size)
	{
		conf->grid[i]->val = champ->inst[j];
		conf->grid[i]->pid = champ->id;
		i++;
		j++;
		i = i % MEM_SIZE;
	}
}

static void		ft_init_process(int i, t_process *process, t_champ *champ,
		t_conf *conf)
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
	process->cycle_to_wait = conf->op_tab[process->op_code].cycles;
	process->ocp = 0;
	i = 0;
	while (i < 4)
		process->fct_args[i++] = 0;
	process->args_size = 0;
	process->ocp_splitted.arg1 = 0;
	process->ocp_splitted.arg2 = 0;
	process->ocp_splitted.arg3 = 0;
	process->ocp_splitted.arg4 = 0;
	conf->grid[process->pc]->pc = process->id_champ;
}

static int		ft_create_process(t_process *process, t_champ *champ,
		t_conf *conf)
{
	if (!(process = (t_process *)malloc(sizeof(*process))))
		return (-1);
	process->next = conf->first_process;
	conf->first_process = process;
	ft_init_process(1, process, champ, conf);
	return (0);
}

static int		ft_order_champ(int i, t_conf *conf)
{
	ft_printf("Acclamés par les spectateurs en furie, les champions font leur \
			entrée dans l'arène...\n");
	while (i <= MAX_PLAYERS)
	{
		if (conf->players[i])
		{
			ft_printf("* Joueur %u, avec un poids de %u octets, %s ! (\"%s\")\
					\n", i, conf->players[i]->inst_size, conf->players[i]->name,
					conf->players[i]->comment);
			ft_init_grid(conf->players[i], conf);
			if (ft_create_process(conf->first_process, conf->players[i],
						conf) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int				ft_init_arena(int i, t_champ *champ, t_conf *conf)
{
	while (i < MEM_SIZE)
	{
		if (!(conf->grid[i] = (t_cell *)malloc(sizeof(*conf->grid[i]))))
			return (-1);
		conf->grid[i]->val = 0;
		conf->grid[i]->pid = 0;
		conf->grid[i]->bold = 0;
		conf->grid[i]->pc = 0;
		i++;
	}
	while (champ)
	{
		conf->players[champ->id] = champ;
		champ = champ->next;
	}
	if (ft_order_champ(1, conf) < 0)
		return (-1);
	return (0);
}
