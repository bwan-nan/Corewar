/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/07/24 17:44:51 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "corewar.h"

typedef unsigned int uint;
typedef unsigned char uchar;

int	preprocess_args(uint mem_i, uchar type, int arg, t_bool idx_mod_care)
{
	// this function does not check error!
	// returns preprocessed arg
	// retuturns -1 if no arg

	int	result;

	if (type == IND_CODE)
		result = (idx_mod_care) ? mem_i + arg % IDX_MOD : mem_i + arg;
	else if (type == DIR_CODE)
		result = arg;
	else if (type == REG_CODE)
		result = arg;
	else if (type == 0)
		result = arg;
	else
		result = -1;

	return (result);
}

void	get_args(unsigned int mem_index, t_ocp ocp, int *args[4], t_bool idx_mod_care)
{
	// first get args from memory using ocp
	// then, check they're correct
	// then, preprocess args by type
	// pseudo code:
	
	// mem_index : index of op code in mem
	// ocp : ocp
	// arg_1 : first arg after ocp, etc

	(*args)[0] = preprocess_args(mem_index, ocp.arg1, (*args)[0], idx_mod_care);
	(*args)[1] = preprocess_args(mem_index, ocp.arg2, (*args)[1], idx_mod_care);
	(*args)[2] = preprocess_args(mem_index, ocp.arg3, (*args)[2], idx_mod_care);
	(*args)[3] = preprocess_args(mem_index, ocp.arg4, (*args)[3], idx_mod_care);
}

t_process	*get_process_by_id(t_process *first_process, uint pid)
{
	t_process *curr;

	curr = first_process;

	while (curr)
	{
		if (curr->id_proc == pid)
			return (curr);
		curr = curr->next;
	}
	return (0);
}

//int		ft_create_process(t_process *process, t_champ *champ, t_conf *conf)
//{
//	if (!(process = (t_process *)malloc(sizeof(*process))))
//		return (-1);
//	process->next = conf->first_process;
//	conf->first_process = process;
//	ft_init_process(process, champ, conf);
//	return (0);
//}

int		c_live(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	unsigned int champ_id = args[0];
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	//get_args(process->pc, ocp, &args, 1);
	(void)ocp;
	conf->players[champ_id]->nb_live += 1;
	conf->last_live = champ_id;
	conf->nb_live += 1;
	conf->last_live = champ_id;
	process->nb_live += 1;
	//printf("function called: \"%s\" by process %d\n", "live", pid);
	//printf("%s ( %d ), a été raporter comme étant en vie.", conf->players[champ_id]->name, args[0]);
	return (1);
}

int		c_ld(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	process->reg[args[1]] = conf->grid[args[0]]->val;
	process->carry = (!conf->grid[args[0]]->val) ? 1 : 0;
	//printf("function called: \"%s\" by process %d\n", "ld", pid);
	return (1);
}

int		c_st(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	conf->grid[args[1]]->val = process->reg[args[0]];
	process->carry = (!conf->grid[args[0]]->val) ? 1 : 0;
	return (1);
}


int		c_add(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	process->reg[args[2]] = process->reg[args[0]] + process->reg[args[1]];
	process->carry = (process->reg[args[2]]) ? 1 : 0;
	return (1);
}

int		c_sub(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	process->reg[args[2]] = process->reg[args[0]] - process->reg[args[1]];
	process->carry = (process->reg[args[2]]) ? 1 : 0;
	return (1);
}

int		c_and(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	process->reg[args[2]] = (process->reg[args[0]] & process->reg[args[1]]);
	process->carry = (process->reg[args[2]]) ? 1 : 0;
	return (1);
}

int		c_or(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	process->reg[args[2]] = (process->reg[args[0]] | process->reg[args[1]]);
	process->carry = (process->reg[args[2]]) ? 1 : 0;
	return (1);
}

int		c_xor(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	process->reg[args[2]] = (process->reg[args[0]] ^ process->reg[args[1]]);
	process->carry = (process->reg[args[2]]) ? 1 : 0;
	return (1);
}

int		c_zjump(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	//get_args(process->pc, ocp, &args, 1);
	(void)ocp;
	process->pc = (process->carry) ? (unsigned int)args[0] : process->pc;
	//int args[4] --> unsigned char fct_args[4]
	//process->pc --> unsigned int
	return (0);
}

int		c_ldi(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	int		sum;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	sum = conf->grid[args[0] + args[1]]->val;
	process->reg[args[2]] = sum;
	process->carry = (!sum) ? 1 : 0;
	return (1);
}

int		c_sti(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	int		sum;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	sum = conf->grid[args[1] + args[2]]->val;
	conf->grid[sum]->val = process->reg[args[0]];
	process->carry = (!sum) ? 1 : 0;
	return (1);
}

int		c_fork(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	//t_process	new_process;
	//int		sum;

	process = get_process_by_id(conf->first_process, pid);
	//get_args(process->pc, ocp, &args, 1);
	(void)ocp;
	(void)args;
	(void)process;
	// to try !
	// new_process = t_process(mem_cpy(&process, sizeof(t_process)));
	// new_process->pc = args[0];
	
	// need to create add_elem before.
	// may similar already exist in libft
	// add_elem(conf->first_process, &new_process);
	return (1);
}

int		c_lld(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 0);
	process->reg[args[1]] = conf->grid[args[0]]->val;
	process->carry = (!conf->grid[args[0]]->val) ? 1 : 0;
	return (1);
}

int		c_lldi(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	int		sum;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 0);
	sum = conf->grid[args[0] + args[1]]->val;
	process->reg[args[2]] = sum;
	process->carry = (!sum) ? 1 : 0;
	return (1);
}

int		c_lfork(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	//t_process	new_process;
	//int		sum;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	//get_args(process->pc, ocp, &args, 0);
	(void)ocp;
	(void)args;
	(void)process;
	// to try !
	// new_process = t_process(mem_cpy(&process, sizeof(t_process)));
	// new_process->pc = args[0];
	
	// need to create add_elem before.
	// may similar already exist in libft
	// add_elem(conf->first_process, &new_process);
	return (1);
}

int		c_aff(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	//ft_printf("arg1:%d, arg2:%d, arg3:%d, arg4:%d\n", args[0], args[1], args[2], args[3]);
	process = get_process_by_id(conf->first_process, pid);
	get_args(process->pc, ocp, &args, 1);
	//ft_printf("register[%02d] : %d\n", process->reg[args[0]]);
	return (1);
}
