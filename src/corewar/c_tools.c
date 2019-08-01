/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/07/30 16:45:39 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				c_check_arg_type(int index1, int index2, int reg3,
		t_process *process)
{
	if (process->ocp_splitted.arg3 != REG_CODE
			|| reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	else if (process->ocp_splitted.arg1 == REG_CODE
			&& (index1 <= 0 || index1 > REG_NUMBER))
		return (1);
	else if (process->ocp_splitted.arg2 == REG_CODE
			&& (index2 <= 0 || index2 > REG_NUMBER))
		return (1);
	return (0);
}

unsigned int	c_modulo_indirect(int val, int pc, int index, t_conf *conf)
{
	pc += (index % IDX_MOD);
	pc = pc % MEM_SIZE;
	while (pc < 0)
		pc += MEM_SIZE;
	if (!val)
		return (pc);
	else
		return (conf->grid[pc]->val);
}

int				c_sum(int index1, int index2, t_process *process)
{
	int		sum;

	sum = index1 + index2;
	sum = sum % MEM_SIZE;
	while (sum < 0)
		sum += MEM_SIZE;
	process->carry = 0;
	if (!sum)
		process->carry = 1;
	return (sum);
}
