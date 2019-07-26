/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/07/26 05:40:19 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		c_live(t_process *process, t_conf *conf)
{
	int		id;

	id = process->fct_args[0];
	if (id <= 0 || id > (int)conf->nb_players)
		return (1);
	process->nb_live++;
	conf->nb_live++;
	conf->players[id]->nb_live++;
	conf->last_live = id;
	return (1);
	//Pas d'OCP pour live !
}

int		c_ld(t_process *process, t_conf *conf)
{
	int		index;
	int		reg1;
	int		pc;

	index = process->fct_args[0];
	reg1 = process->fct_args[1];
	pc = process->pc;
	if (process->ocp_split.arg2 != REG_CODE || reg1 <= 0 || reg1 > REG_NUMBER)
		return (1);
	if (process->ocp_split.arg1 == IND_CODE)
	{
		pc += (index % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		process->reg[reg1 - 1] = conf->grid[pc]->val;
		index = conf->grid[pc]->val;
	}
	else if (process->ocp_split.arg1 == DIR_CODE)
		process->reg[reg1 - 1] = index;
	else
		return (1);
	process->carry = 0;
	if (!index)
		process->carry = 1;
	return (1);
	//carry = 1 seulement si la valeur de args[0] (index) vaut 0 !
}

int		c_st(t_process *process, t_conf *conf)
{
	int		reg1;
	int		index;
	int		pc;

	reg1 = process->fct_args[0];
	index = process->fct_args[1];
	pc = process->pc;
	if (process->ocp_split.arg1 != REG_CODE || reg1 <= 0 || reg1 > REG_NUMBER)
		return (1);
	if (process->ocp_split.arg2 == IND_CODE)
	{
		pc += (index % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		conf->grid[pc]->val = process->reg[reg1 - 1];
		conf->grid[pc]->pid = process->id_champ;
	}
	else if (process->ocp_split.arg2 == REG_CODE)
	{
		if (index > 0 && index <= REG_NUMBER)
			process->reg[index - 1] = process->reg[reg1 - 1];
	}
	//pas de carry pour st !
	return (1);
}

int		c_add(t_process *process, t_conf *conf)
{
	int		reg1;
	int		reg2;
	int		reg3;

	(void)conf;
	reg1 = process->fct_args[0];
	reg2 = process->fct_args[1];
	reg3 = process->fct_args[2];
	if (process->ocp_split.arg1 != REG_CODE
			|| process->ocp_split.arg2 != REG_CODE
			|| process->ocp_split.arg3 != REG_CODE
			|| reg1 <= 0 || reg1 > REG_NUMBER
			|| reg2 <= 0 || reg2 > REG_NUMBER
			|| reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	process->reg[reg3 - 1] = process->reg[reg1 - 1] + process->reg[reg2 - 1];
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
	//carry = 1 seulement si la valeur de args[0] + args[1] vaut 0 !
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
	if (process->ocp_split.arg1 != REG_CODE
			|| process->ocp_split.arg2 != REG_CODE
			|| process->ocp_split.arg3 != REG_CODE
			|| reg1 <= 0 || reg1 > REG_NUMBER
			|| reg2 <= 0 || reg2 > REG_NUMBER
			|| reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	process->reg[reg3 - 1] = process->reg[reg1 - 1] - process->reg[reg2 - 1];
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
	//carry = 1 seulement si la valeur de args[0] - args[1] vaut 0 !
}

int		c_and(t_process *process, t_conf *conf)
{
	int		index1;
	int		index2;
	int		reg3;
	int		pc;

	(void)conf;
	index1 = process->fct_args[0];
	index2 = process->fct_args[1];
	reg3 = process->fct_args[2];
	pc = process->pc;
	if (process->ocp_split.arg3 != REG_CODE || reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	else if (process->ocp_split.arg1 == REG_CODE
			&& (index1 <= 0 || index1 > REG_NUMBER))
		return (1);
	else if (process->ocp_split.arg2 == REG_CODE
			&& (index2 <= 0 || index2 > REG_NUMBER))
		return (1);
	if (process->ocp_split.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_split.arg1 == IND_CODE)
	{
		pc += (index1 % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index1 = conf->grid[pc]->val;
	}
	if (process->ocp_split.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_split.arg2 == IND_CODE)
	{
		pc = process->pc;
		pc += (index2 % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index2 = conf->grid[pc]->val;
	}
	process->reg[reg3 - 1] = index1 & index2;
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
	//carry = 1 seulement si la valeur de args[0] & args[1] vaut 0 !
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
	if (process->ocp_split.arg3 != REG_CODE || reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	else if (process->ocp_split.arg1 == REG_CODE
			&& (index1 <= 0 || index1 > REG_NUMBER))
		return (1);
	else if (process->ocp_split.arg2 == REG_CODE
			&& (index2 <= 0 || index2 > REG_NUMBER))
		return (1);
	if (process->ocp_split.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_split.arg1 == IND_CODE)
	{
		pc += (index1 % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index1 = conf->grid[pc]->val;
	}
	if (process->ocp_split.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_split.arg2 == IND_CODE)
	{
		pc = process->pc;
		pc += (index2 % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index2 = conf->grid[pc]->val;
	}
	process->reg[reg3 - 1] = index1 | index2;
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
	//carry = 1 seulement si la valeur de args[0] | args[1] vaut 0 !
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
	if (process->ocp_split.arg3 != REG_CODE || reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	else if (process->ocp_split.arg1 == REG_CODE
			&& (index1 <= 0 || index1 > REG_NUMBER))
		return (1);
	else if (process->ocp_split.arg2 == REG_CODE
			&& (index2 <= 0 || index2 > REG_NUMBER))
		return (1);
	if (process->ocp_split.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_split.arg1 == IND_CODE)
	{
		pc += (index1 % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index1 = conf->grid[pc]->val;
	}
	if (process->ocp_split.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_split.arg2 == IND_CODE)
	{
		pc = process->pc;
		pc += (index2 % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index2 = conf->grid[pc]->val;
	}
	process->reg[reg3 - 1] = index1 ^ index2;
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
	//carry = 1 seulement si la valeur de args[0] ^ args[1] vaut 0 !
}

int		c_zjump(t_process *process, t_conf *conf)
{
	int		index;

	(void)conf;
	index = process->fct_args[0];
	index = index % IDX_MOD;
	if (process->carry)
	{
		process->pc += index;
		process->pc = process->pc % MEM_SIZE;
		while (process->pc < 0)
			process->pc += MEM_SIZE;
		return (0);
	}
	return (1);
	// Pas d'OCP pour jump !
}

int		c_ldi(t_process *process, t_conf *conf)
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
	if (process->ocp_split.arg3 != REG_CODE || reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	else if (process->ocp_split.arg1 == REG_CODE
			&& (index1 <= 0 || index1 > REG_NUMBER))
		return (1);
	else if (process->ocp_split.arg2 == REG_CODE
			&& (index2 <= 0 || index2 > REG_NUMBER))
		return (1);
	if (process->ocp_split.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_split.arg1 == IND_CODE)
	{
		pc += (index1 % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index1 = conf->grid[pc]->val;
	}
	if (process->ocp_split.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_split.arg2 == IND_CODE)
		return (1);
	sum = index1 + index2;
	sum = sum % MEM_SIZE;
	while (sum < 0)
		sum += MEM_SIZE;
	process->reg[reg3 - 1] = conf->grid[sum]->val;
	/*process->carry = 0;
	  if (!process->reg[reg3 - 1])
	  process->carry = 1;*/
	return (1);
	//pas de carry sur le sujet/doc mais a vérifier sur la vm zaz, sinon
	//carry = 1 seulement si la valeur de grid[args[0] + args[1]] vaut 0 !
}

int		c_sti(t_process *process, t_conf *conf)
{
	int		reg1;
	int		index2;
	int		index3;
	int		pc;
	int		sum;

	reg1 = process->fct_args[0];
	index2 = process->fct_args[1];
	index3 = process->fct_args[2];
	pc = process->pc;
	sum = 0;
	if (process->ocp_split.arg1 != REG_CODE || reg1 <= 0 || reg1 > REG_NUMBER)
		return (1);
	else if (process->ocp_split.arg2 == REG_CODE
			&& (index2 <= 0 || index2 > REG_NUMBER))
		return (1);
	else if (process->ocp_split.arg3 == REG_CODE
			&& (index3 <= 0 || index3 > REG_NUMBER))
		return (1);
	if (process->ocp_split.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_split.arg2 == IND_CODE)
	{
		pc += (index2 % IDX_MOD);
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index2 = conf->grid[pc]->val;
	}
	if (process->ocp_split.arg3 == REG_CODE)
		index3 = process->reg[index3 - 1];
	else if (process->ocp_split.arg2 == IND_CODE)
		return (1);
	sum = index2 + index3;
	sum = sum % MEM_SIZE;
	while (sum < 0)
		sum += MEM_SIZE;
	conf->grid[sum]->val = process->reg[reg1 - 1];
	conf->grid[sum]->pid = process->id_champ;
	/*process->carry = 0;
	  if (!process->reg[reg1 - 1])
	  process->carry = 1;*/
	return (1);
	//pas de carry sur le sujet/doc mais a vérifier sur la vm zaz, sinon
	//carry = 1 seulement si la valeur de args[0] vaut 0 !
}
static void		ft_init_fork(t_process *new, t_process *process, int pc, t_conf *conf)
{
	int		i;

	conf->nb_process++;
	conf->total_process++;
	conf->players[process->id_champ]->nb_process++;
	new->id_proc = conf->total_process;
	new->id_champ = process->id_champ;
	new->nb_live = 0;
	i = 0;
	while (i < REG_NUMBER)
	{
		new->reg[i] = process->reg[i];
		i++;
	}
	new->pc = pc;
	new->carry = 0;
	new->op_code = conf->grid[new->pc]->val - 1;
	new->cycle_to_wait = conf->op_tab[new->op_code].cycles;
	new->ocp = 0;
	i = 0;
	while (i < 4)
		new->fct_args[i++] = 0;
	new->args_size = 0;
	new->ocp_split.arg1 = 0;
	new->ocp_split.arg2 = 0;
	new->ocp_split.arg3 = 0;
	new->ocp_split.arg4 = 0;
	conf->grid[new->pc]->pc = new->id_champ;
}

int		c_fork(t_process *process, t_conf *conf)
{
	t_process		*new;
	int				pc;

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
	//Pas d'OCP ni de carry pour fork !
}

int		c_lld(t_process *process, t_conf *conf)
{
	int		index;
	int		reg1;
	int		pc;

	index = process->fct_args[0];
	reg1 = process->fct_args[1];
	pc = process->pc;
	if (process->ocp_split.arg2 != REG_CODE || reg1 <= 0 || reg1 > REG_NUMBER)
		return (1);
	if (process->ocp_split.arg1 == IND_CODE)
	{
		pc += index;
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		process->reg[reg1 - 1] = conf->grid[pc]->val;
		index = conf->grid[pc]->val;
	}
	else if (process->ocp_split.arg1 == DIR_CODE)
		process->reg[reg1 - 1] = index;
	else
		return (1);
	process->carry = 0;
	if (!index)
		process->carry = 1;
	return (1);
	//carry = 1 seulement si la valeur de args[0] (index) vaut 0 !
}

int		c_lldi(t_process *process, t_conf *conf)
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
	if (process->ocp_split.arg3 != REG_CODE || reg3 <= 0 || reg3 > REG_NUMBER)
		return (1);
	else if (process->ocp_split.arg1 == REG_CODE
			&& (index1 <= 0 || index1 > REG_NUMBER))
		return (1);
	else if (process->ocp_split.arg2 == REG_CODE
			&& (index2 <= 0 || index2 > REG_NUMBER))
		return (1);
	if (process->ocp_split.arg1 == REG_CODE)
		index1 = process->reg[index1 - 1];
	else if (process->ocp_split.arg1 == IND_CODE)
	{
		pc += index1;
		pc = pc % MEM_SIZE;
		while (pc < 0)
			pc += MEM_SIZE;
		index1 = conf->grid[pc]->val;
	}
	if (process->ocp_split.arg2 == REG_CODE)
		index2 = process->reg[index2 - 1];
	else if (process->ocp_split.arg2 == IND_CODE)
		return (1);
	sum = index1 + index2;
	sum = sum % MEM_SIZE;
	while (sum < 0)
		sum += MEM_SIZE;
	process->reg[reg3 - 1] = conf->grid[sum]->val;
	process->carry = 0;
	if (!process->reg[reg3 - 1])
		process->carry = 1;
	return (1);
	//carry = 1 seulement si la valeur de grid[args[0] + args[1]] vaut 0 !
	return (1);
}

int		c_lfork(t_process *process, t_conf *conf)
{
	t_process		*new;
	int				pc;

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
	//Pas d'OCP ni de carry pour lfork !
}

int		c_aff(t_process *process, t_conf *conf)
{
	int		reg1;

	(void)conf;
	reg1 = process->fct_args[0];
	if (process->ocp_split.arg1 != REG_CODE || reg1 <= 0 || reg1 > REG_NUMBER)
		return (1);
	reg1 = process->reg[reg1 - 1];
	reg1 = reg1 % 256;
	ft_printf("%c", reg1);
	return (1);
	//Pas de carry mais il y a un OCP ! (illogique)
}
