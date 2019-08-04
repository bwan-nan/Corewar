/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/04 06:52:53 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_reinit_process(t_process *process)
{
	process->ocp = 0;
	process->fct_args[0] = 0;
	process->fct_args[1] = 0;
	process->fct_args[2] = 0;
	process->fct_args[3] = 0;
	process->args_size = 0;
	process->ocp_splitted.arg1 = 0;
	process->ocp_splitted.arg2 = 0;
	process->ocp_splitted.arg3 = 0;
	process->ocp_splitted.arg4 = 0;
}

static int		ft_get_op_code(t_process *process, t_conf *conf)
{
	unsigned int	pc;

	pc = process->pc;
	if (process->op_code < D_OP_MAX)
	{
		if (conf->op_tab[process->op_code].ocp)
			process->ocp = conf->grid[(pc + 1) % MEM_SIZE]->val;
		return (0);
	}
	/*else if (process->op_code == UCHAR_MAX)
	  return (0);
	  else
	  return (-16);*/
	else
		process->op_code = UCHAR_MAX;
	return (0);
}

static int		ft_apply_inst(int ret, t_process *process, t_conf *conf)
{
	conf->grid[process->pc]->pc = 0;
	if (process->op_code >= D_OP_MAX)
		process->pc = (process->pc + 1) % MEM_SIZE;
	else
	{
		if (ft_check_args_size(process, conf) < 0)
			return (-17);
		if ((ret = conf->op_inst[process->op_code](process, conf)) < 0)
			return (-1);
		else if (ret)
			process->pc = (process->pc + process->args_size) % MEM_SIZE;
	}
	ft_print_visu(2, process, conf);
	conf->grid[process->pc]->pc = process->id_champ;
	return (0);
}

static int		ft_check_process(int ret, t_process *process, t_conf *conf)
{
	process->cycle_to_wait--;
	if (!process->cycle_to_wait)
	{
		ft_reinit_process(process);
		//if (ft_get_op_code(process, conf) < 0)
		//	return (-16);
		if ((ret = ft_apply_inst(0, process, conf)) < 0)
			return (ret);
		ft_print_visu(3, process, conf);
		ft_reinit_process(process);
		process->op_code = conf->grid[process->pc]->val - 1;
		if (ft_get_op_code(process, conf) < 0)
			return (-16);
		if (process->op_code == UCHAR_MAX)
			process->cycle_to_wait = 1;
		else
			process->cycle_to_wait = conf->op_tab[process->op_code].cycles;
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
