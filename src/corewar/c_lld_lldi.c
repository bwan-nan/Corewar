/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_lld_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/07/30 15:02:00 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_no_mod_ind(int pc, int index, t_conf *conf)
{
	pc += index;
	pc = pc % MEM_SIZE;
	while (pc < 0)
		pc += MEM_SIZE;
	return (conf->grid[pc]->val);
}

int			c_lld(t_process *process, t_conf *conf)
{
	int		index;
	int		reg1;
	int		pc;

	index = process->fct_args[0];
	reg1 = process->fct_args[1];
	pc = process->pc;
	if (process->ocp_splitted.arg2 != REG_CODE
		|| reg1 <= 0 || reg1 > REG_NUMBER)
		return (1);
	if (process->ocp_splitted.arg1 == IND_CODE)
	{
		index = ft_no_mod_ind(pc, index, conf);
		process->reg[reg1 - 1] = index;
	}
	else if (process->ocp_splitted.arg1 == DIR_CODE)
		process->reg[reg1 - 1] = index;
	else
		return (1);
	process->carry = 0;
	if (!index)
		process->carry = 1;
	return (1);
}

int			c_lldi(t_process *process, t_conf *conf)
{
	int		index1;
	int		index2;
	int		reg3;
	int		pc;
	int		sum;

	index1 = process->fct_args[0];
	index2 = process->fct_args[1];
	reg3 = process->fct_args[2];
	pc = process->pc;
	sum = 0;
	if (c_check_arg_type(index1, index2, reg3, process) == 1)
		return (1);
	if (process->ocp_splitted.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_splitted.arg1 == IND_CODE)
		index1 = ft_no_mod_ind(pc, index1, conf);
	if (process->ocp_splitted.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_splitted.arg2 == IND_CODE)
		return (1);
	sum = c_sum(index1, index2, process);
	process->reg[reg3 - 1] = conf->grid[sum]->val;
	return (1);
}
