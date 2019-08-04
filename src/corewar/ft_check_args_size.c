/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/04 02:26:26 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_decode_arg(int shift, int pc, int *fct_arg, t_conf *conf)
{
	ft_memcpy(fct_arg, &conf->grid[pc]->val, 1);
	if (shift)
		*fct_arg = *fct_arg << 8;
	pc++;
	pc = pc % MEM_SIZE;
	return (pc);
}

static int		ft_decode_direct(int pc, int *fct_arg, t_process *process,
		t_conf *conf)
{
	process->args_size += conf->op_tab[process->op_code].dir_size;
	pc = ft_decode_arg(1, pc, fct_arg, conf);
	pc = ft_decode_arg(0, pc, fct_arg, conf);
	if (conf->op_tab[process->op_code].dir_size == 4)
	{
		*fct_arg = *fct_arg << 8;
		pc = ft_decode_arg(1, pc, fct_arg, conf);
		pc = ft_decode_arg(0, pc, fct_arg, conf);
	}
	else if (conf->op_tab[process->op_code].dir_size == 2)
		*fct_arg = (short)*fct_arg;
	return (pc);
}

static int		ft_check_ocp(int pc, t_ocp ocp_splitted, t_process *process,
		t_conf *conf)
{
	int			i;

	i = 0;
	while (i < conf->op_tab[process->op_code].nb_args)
	{
		//if (((char *)(&ocp_splitted))[i] == 0)
		//	return (pc);
		if (((char *)(&ocp_splitted))[i] == 1)
		{
			process->args_size++;
			pc = ft_decode_arg(0, pc, &process->fct_args[i], conf);
		}
		else if (((char *)(&ocp_splitted))[i] == 2)
			pc = ft_decode_direct(pc, &process->fct_args[i], process, conf);
		else if (((char *)(&ocp_splitted))[i] == 3)
		{
			process->args_size += 2;
			pc = ft_decode_arg(1, pc, &process->fct_args[i], conf);
			pc = ft_decode_arg(0, pc, &process->fct_args[i], conf);
			process->fct_args[i] = (short)process->fct_args[i];
		}
		else if (((char *)(&ocp_splitted))[i] != 0)
			return (-17);
		i++;
	}
	return (0);
}

static int		ft_decode_ocp(int pc, t_process *process, t_conf *conf)
{
	process->args_size++;
	pc++;
	pc = pc % MEM_SIZE;
	process->ocp = conf->grid[pc]->val;
	process->ocp = process->ocp & 0xFF;
	process->ocp_splitted.arg1 = process->ocp >> 6;
	process->ocp = process->ocp & 0x3F;
	process->ocp_splitted.arg2 = process->ocp >> 4;
	process->ocp = process->ocp & 0x0F;
	process->ocp_splitted.arg3 = process->ocp >> 2;
	process->ocp = process->ocp & 0x03;
	process->ocp_splitted.arg4 = process->ocp;
	pc++;
	pc = pc % MEM_SIZE;
	return (pc);
}

int				ft_check_args_size(t_process *process, t_conf *conf)
{
	int			pc;

	pc = (int)process->pc;
	process->args_size = 1;
	process->ocp_splitted.arg1 = 0;
	process->ocp_splitted.arg2 = 0;
	process->ocp_splitted.arg3 = 0;
	process->ocp_splitted.arg4 = 0;
	if (conf->op_tab[process->op_code].ocp)
	{
		pc = ft_decode_ocp(pc, process, conf);
		if (ft_check_ocp(pc, process->ocp_splitted, process, conf) < 0)
			return (-17);
	}
	else
	{
		pc++;
		pc = pc % MEM_SIZE;
		ft_decode_direct(pc, &process->fct_args[0], process, conf);
	}
	return (0);
}
