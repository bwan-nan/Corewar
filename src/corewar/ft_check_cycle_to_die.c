/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cycle_to_die.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/30 15:08:32 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_kill_process(t_process *last, t_process *next,
		t_process *process, t_conf *conf)
{
	if (process == conf->first_process)
		conf->first_process = next;
	else
		last->next = next;
	conf->grid[process->pc]->pc = 0;
	conf->players[process->id_champ]->nb_process--;
	conf->nb_process--;
	if (conf->opt[1])
		ft_printf("Le processus %u créé par le joueur %u a été mis à mort !\n",
				process->id_proc, process->id_champ);
	free(process);
}

static void		ft_purge_process(t_process *process, t_conf *conf)
{
	t_process	*last;
	t_process	*next;

	last = process;
	next = process->next;
	while (process)
	{
		if (!process->nb_live)
		{
			ft_kill_process(last, next, process, conf);
			process = next;
		}
		else
		{
			process->nb_live = 0;
			last = process;
		}
		process = next;
		if (process)
			next = process->next;
		else
			next = NULL;
	}
}

void			ft_check_cycle_to_die(t_conf *conf)
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
