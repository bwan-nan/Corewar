/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_add_sub_and_or_xor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/08/03 05:17:29 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		c_add(t_process *process, t_conf *conf)
{
	int		reg1;
	int		reg2;
	int		reg3;

	(void)conf;
	reg1 = process->fct_args[0];
	reg2 = process->fct_args[1];
	reg3 = process->fct_args[2];
	if (process->ocp_splitted.arg1 != REG_CODE
			|| process->ocp_splitted.arg2 != REG_CODE
			|| process->ocp_splitted.arg3 != REG_CODE
			|| reg1 <= 0 || reg1 > REG_NUMBER
			|| reg2 <= 0 || reg2 > REG_NUMBER
			|| reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	process->reg[reg3 - 1] = process->reg[reg1 - 1] + process->reg[reg2 - 1];
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
}

int		c_sub(t_process *process, t_conf *conf)
{
	int		reg1;
	int		reg2;
	int		reg3;

	(void)conf;
	reg1 = process->fct_args[0];
	reg2 = process->fct_args[1];
	reg3 = process->fct_args[2];
	if (process->ocp_splitted.arg1 != REG_CODE
			|| process->ocp_splitted.arg2 != REG_CODE
			|| process->ocp_splitted.arg3 != REG_CODE
			|| reg1 <= 0 || reg1 > REG_NUMBER
			|| reg2 <= 0 || reg2 > REG_NUMBER
			|| reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	process->reg[reg3 - 1] = process->reg[reg1 - 1] - process->reg[reg2 - 1];
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
}

int		c_and(t_process *process, t_conf *conf)
{
	int		index1;
	int		index2;
	int		reg3;
	int		pc;

	index1 = process->fct_args[0];
	index2 = process->fct_args[1];
	reg3 = process->fct_args[2];
	pc = process->pc;
	if (c_check_arg_type(index1, index2, reg3, process) == 1)
		return (1);
	if (process->ocp_splitted.arg3 != REG_CODE)
		return (1);
	if (process->ocp_splitted.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_splitted.arg1 == IND_CODE)
		index1 = c_modulo_indirect(1, pc, index1, conf);
	if (process->ocp_splitted.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_splitted.arg2 == IND_CODE)
		index2 = c_modulo_indirect(1, pc, index2, conf);
	process->reg[reg3 - 1] = index1 & index2;
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
}

int		c_or(t_process *process, t_conf *conf)
{
	int		index1;
	int		index2;
	int		reg3;
	int		pc;

	index1 = process->fct_args[0];
	index2 = process->fct_args[1];
	reg3 = process->fct_args[2];
	pc = process->pc;
	if (c_check_arg_type(index1, index2, reg3, process) == 1)
		return (1);
	if (process->ocp_splitted.arg3 != REG_CODE)
		return (1);
	if (process->ocp_splitted.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_splitted.arg1 == IND_CODE)
		index1 = c_modulo_indirect(1, pc, index1, conf);
	if (process->ocp_splitted.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_splitted.arg2 == IND_CODE)
		index2 = c_modulo_indirect(1, pc, index2, conf);
	process->reg[reg3 - 1] = index1 | index2;
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
}

int		c_xor(t_process *process, t_conf *conf)
{
	int		index1;
	int		index2;
	int		reg3;
	int		pc;

	index1 = process->fct_args[0];
	index2 = process->fct_args[1];
	reg3 = process->fct_args[2];
	pc = process->pc;
	if (c_check_arg_type(index1, index2, reg3, process) == 1)
		return (1);
	if (process->ocp_splitted.arg3 != REG_CODE)
		return (1);
	if (process->ocp_splitted.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_splitted.arg1 == IND_CODE)
		index1 = c_modulo_indirect(1, pc, index1, conf);
	if (process->ocp_splitted.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_splitted.arg2 == IND_CODE)
		index2 = c_modulo_indirect(1, pc, index2, conf);
	process->reg[reg3 - 1] = index1 ^ index2;
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
}
