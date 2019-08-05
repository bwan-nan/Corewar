/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/05 07:33:01 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_get_ocp(t_process *process, t_conf *conf)
{
	unsigned int	pc;

	pc = process->pc;
	if (process->op_code < D_OP_MAX)
	{
		if (conf->op_tab[process->op_code].ocp)
			process->ocp = conf->grid[(pc + 1) % MEM_SIZE]->val;
		return (0);
	}
	else
		process->op_code = UCHAR_MAX;
	return (0);
}

static void		ft_update_op_code(t_process *process, t_conf *conf)
{
	if (((unsigned int)process->op_code < (unsigned int)D_OP_MAX)
			&& (conf->op_tab[process->op_code].cycles - process->cycle_to_wait)
			== 0)
	{
		if (process->op_code != conf->grid[process->pc]->val - 1)
		{
			process->op_code = conf->grid[process->pc]->val - 1;
			if (((unsigned int)conf->grid[process->pc]->val - 1)
					< (unsigned int)D_OP_MAX)
			{
				process->cycle_to_wait = conf->op_tab[process->op_code].cycles;
				process->ocp = conf->grid[(process->pc + 1) % MEM_SIZE]->val;
			}
			else
				process->cycle_to_wait = 1;
		}
	}
}

static void		ft_update_empty_cell(t_process *process, t_conf *conf)
{
	process->op_code = conf->grid[process->pc]->val - 1;
	if (process->op_code != UCHAR_MAX)
	{
		process->cycle_to_wait = conf->op_tab[process->op_code].cycles - 1;
		process->ocp = conf->grid[(process->pc + 1) % MEM_SIZE]->val;
		ft_print_visu(3, process, conf);
	}
}

static int		ft_check_process(int ret, t_process *process, t_conf *conf)
{
	ft_update_op_code(process, conf);
	process->cycle_to_wait--;
	if (!process->cycle_to_wait)
	{
		ft_init_process(1, process, NULL, conf);
		if (process->op_code == UCHAR_MAX
				&& ((unsigned int)conf->grid[process->pc]->val - 1
				< (unsigned int)D_OP_MAX))
			ft_update_empty_cell(process, conf);
		else
		{
			if ((ret = ft_apply_inst(0, process, conf)) < 0)
				return (ret);
			ft_print_visu(3, process, conf);
			process->op_code = conf->grid[process->pc]->val - 1;
			if (ft_get_ocp(process, conf) < 0)
				return (-16);
			if (process->op_code == UCHAR_MAX)
				process->cycle_to_wait = 1;
			else
				process->cycle_to_wait = conf->op_tab[process->op_code].cycles;
		}
	}
	return (0);
}
int				ft_launch_arena(int ret, t_process *process, t_conf *conf)
{
	ft_print_visu(0, process, conf);
	conf->cycle++;
	while (conf->nb_process && (!conf->opt[0] || conf->cycle <= conf->dump)
			&& conf->cycle_to_die <= CYCLE_TO_DIE)
	{
		ft_print_visu(1, process, conf);
		process = conf->first_process;
		while (process)
		{
			if ((ret = ft_check_process(0, process, conf)) < 0)
				return (ret);
			process = process->next;
		}
		if (conf->period == conf->cycle_to_die)
			ft_check_cycle_to_die(conf);
		ft_print_visu(4, process, conf);
		conf->period++;
		conf->cycle++;
	}
	ft_print_visu(5, process, conf);
	return (0);
}
