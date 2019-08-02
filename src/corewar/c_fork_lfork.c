/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_fork_lfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/08/02 01:21:08 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_update_conf(t_process *new, t_process *process, t_conf *conf)
{
	conf->nb_process++;
	conf->players[process->id_champ]->nb_process++;
	conf->grid[new->pc]->pc = new->id_champ;
}

static void		ft_init_ocp(t_process *new)
{
	int		i;

	i = 0;
	while (i < 4)
		new->fct_args[i++] = 0;
	new->ocp = 0;
	new->args_size = 0;
	new->ocp_splitted.arg1 = 0;
	new->ocp_splitted.arg2 = 0;
	new->ocp_splitted.arg3 = 0;
	new->ocp_splitted.arg4 = 0;
}

static void		ft_init_fork(t_process *new, t_process *process, int pc,
		t_conf *conf)
{
	int			i;

	new->id_champ = process->id_champ;
	new->id_proc = ++conf->total_process;
	new->nb_live = 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		new->reg[i] = process->reg[i];
		i++;
	}
	new->pc = pc;
	new->carry = process->carry;
	new->op_code = conf->grid[new->pc]->val - 1;
	if (new->op_code == UCHAR_MAX)
		new->cycle_to_wait = 1;
	else
		new->cycle_to_wait = conf->op_tab[new->op_code].cycles;
	ft_init_ocp(new);
	ft_update_conf(new, process, conf);
}

int				c_fork(t_process *process, t_conf *conf)
{
	t_process	*new;
	int			pc;

	new = NULL;
	pc = process->pc;
	pc += (process->fct_args[0] % IDX_MOD);
	pc = pc % MEM_SIZE;
	while (pc < 0)
		pc += MEM_SIZE;
	if (!(new = (t_process *)malloc(sizeof(*process))))
		return (-1);
	new->next = conf->first_process;
	conf->first_process = new;
	ft_init_fork(new, process, pc, conf);
	return (1);
}

int				c_lfork(t_process *process, t_conf *conf)
{
	t_process	*new;
	int			pc;

	new = NULL;
	pc = process->pc;
	pc += process->fct_args[0];
	pc = pc % MEM_SIZE;
	while (pc < 0)
		pc += MEM_SIZE;
	if (!(new = (t_process *)malloc(sizeof(*process))))
		return (-1);
	new->next = conf->first_process;
	conf->first_process = new;
	ft_init_fork(new, process, pc, conf);
	return (1);
}
