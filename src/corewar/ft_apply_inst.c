/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_inst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/05 06:58:29 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_apply_inst(int ret, t_process *process, t_conf *conf)
{
	conf->grid[process->pc]->nb_pc--;
	if (!conf->grid[process->pc]->nb_pc)
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
	conf->grid[process->pc]->pc = process->id_champ;
	conf->grid[process->pc]->nb_pc++;
	ft_print_visu(2, process, conf);
	return (0);
}
