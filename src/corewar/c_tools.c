/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/08/02 16:32:53 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			c_check_arg_type(int index1, int index2, int index3,
		t_process *process)
{
	if (process->ocp_splitted.arg1 == REG_CODE
			&& (index1 <= 0 || index1 > REG_NUMBER))
		return (1);
	else if (process->ocp_splitted.arg2 == REG_CODE
			&& (index2 <= 0 || index2 > REG_NUMBER))
		return (1);
	else if (process->ocp_splitted.arg3 == REG_CODE
			&& (index3 <= 0 || index3 > REG_NUMBER))
		return (1);
	return (0);
}

int			c_modulo_indirect(int val, int pc, int index, t_conf *conf)
{
	pc += (index % IDX_MOD);
	pc = pc % MEM_SIZE;
	while (pc < 0)
		pc += MEM_SIZE;
	if (!val)
		return (pc);
	else
	{
		val = conf->grid[pc]->val;
		val = val << 8;
		pc = (pc + 1) % MEM_SIZE;
		val += conf->grid[pc]->val;
		val = val << 8;
		pc = (pc + 1) % MEM_SIZE;
		val += conf->grid[pc]->val;
		val = val << 8;
		pc = (pc + 1) % MEM_SIZE;
		val += conf->grid[pc]->val;
		return (val);
	}
}

int			c_sum(int index1, int index2, t_process *process)
{
	int		sum;

	sum = (index1 + index2) % IDX_MOD;
	sum += process->pc;
	sum = sum % MEM_SIZE;
	while (sum < 0)
		sum += MEM_SIZE;
	return (sum);
}

void		c_store_int(int pc, int reg1, t_process *process, t_conf *conf)
{
	conf->grid[pc]->val = process->reg[reg1 - 1] >> 24;
	conf->grid[pc]->pid = process->id_champ;
	conf->grid[pc]->bold = D_GRID_ST;
	pc = (pc + 1) % MEM_SIZE;
	conf->grid[pc]->val = (process->reg[reg1 - 1] & 0x00FF0000) >> 16;
	conf->grid[pc]->pid = process->id_champ;
	conf->grid[pc]->bold = D_GRID_ST;
	pc = (pc + 1) % MEM_SIZE;
	conf->grid[pc]->val = (process->reg[reg1 - 1] & 0x0000FF00) >> 8;
	conf->grid[pc]->pid = process->id_champ;
	conf->grid[pc]->bold = D_GRID_ST;
	pc = (pc + 1) % MEM_SIZE;
	conf->grid[pc]->val = process->reg[reg1 - 1] & 0x000000FF;
	conf->grid[pc]->pid = process->id_champ;
	conf->grid[pc]->bold = D_GRID_ST;
}

void		c_read_int(int pc, int reg1, t_process *process, t_conf *conf)
{
	ft_memcpy(&process->reg[reg1 - 1], &conf->grid[pc]->val, 1);
	process->reg[reg1 - 1] = process->reg[reg1 - 1] << 8;
	pc = (pc + 1) % MEM_SIZE;
	ft_memcpy(&process->reg[reg1 - 1], &conf->grid[pc]->val, 1);
	process->reg[reg1 - 1] = process->reg[reg1 - 1] << 8;
	pc = (pc + 1) % MEM_SIZE;
	ft_memcpy(&process->reg[reg1 - 1], &conf->grid[pc]->val, 1);
	process->reg[reg1 - 1] = process->reg[reg1 - 1] << 8;
	pc = (pc + 1) % MEM_SIZE;
	ft_memcpy(&process->reg[reg1 - 1], &conf->grid[pc]->val, 1);
}
