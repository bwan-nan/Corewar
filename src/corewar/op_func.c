/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/07/19 02:22:35 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "corewar.h"

typedef unsigned int uint;
typedef unsigned char uchar;

//int	preprocess_args(uint mem_i, uchar type, int arg, t_bool idx_mod_care)
//{
//	// this function does not check error!
//	// returns preprocessed arg
//	// retuturns -1 if no arg
//
//	int	result;
//
//	if (type == IND_CODE)
//		result = (idx_mod_care) ? mem_i + arg % IDX_MOD : mem_i + arg;
//	else if (type == DIR_CODE)
//		result = arg;
//	else if (type == REG_CODE)
//		result = arg;
//	else if (type == 0)
//		result = arg;
//	else
//		result = -1;
//
//	return (result);
//}
//
//int[4]	get_args()
//{
//	// first get args from memory using ocp
//	// then, check they're correct
//	// then, preprocess args by type
//	// pseudo code:
//	
//	int	args[4];
//
//	// mem_index : index of op code in mem
//	// ocp : ocp
//	// arg_1 : first arg after ocp, etc
//
//	args[0] = preprocess_arg(mem_index, ocp.arg1, arg_1);
//	args[1] = preprocess_arg(mem_index, ocp.arg2, arg_2);
//	args[2] = preprocess_arg(mem_index, ocp.arg3, arg_3);
//	args[3] = preprocess_arg(mem_index, ocp.arg4, arg_4);
//	return (args);
//}

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
//	champ = champ->next;
//	return (0);
//}

void	c_live(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	unsigned int champ_id = args[0];

	(void)ocp;
	conf->players[champ_id]->nb_live += 1;
	conf->nb_live += 1;

	printf("function called: \"%s\" by process %d\n", "live", pid);
	printf("%s ( %d ), a été raporter comme étant en vie.", conf->players[champ_id]->name, args[0]);
}

void	c_ld(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	process->reg[args[1]] = conf->grid[args[0]]->val;
	process->carry = (!conf->grid[args[0]]->val) ? 1 : 0;
	printf("function called: \"%s\" by process %d\n", "ld", pid);
}

void	c_st(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	conf->grid[args[1]]->val = process->reg[args[0]];
	process->carry = (!conf->grid[args[0]]->val) ? 1 : 0;
}


void	c_add(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	process->reg[args[2]] = process->reg[args[0]] + process->reg[args[1]];
	process->carry = (process->reg[args[2]]) ? 1 : 0;
}

void	c_sub(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	process->reg[args[2]] = process->reg[args[0]] - process->reg[args[1]];
	process->carry = (process->reg[args[2]]) ? 1 : 0;
}

void	c_and(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	process->reg[args[2]] = (process->reg[args[0]] & process->reg[args[1]]);
	process->carry = (process->reg[args[2]]) ? 1 : 0;
}

void	c_or(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	process->reg[args[2]] = (process->reg[args[0]] | process->reg[args[1]]);
	process->carry = (process->reg[args[2]]) ? 1 : 0;
}

void	c_xor(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	process->reg[args[2]] = (process->reg[args[0]] ^ process->reg[args[1]]);
	process->carry = (process->reg[args[2]]) ? 1 : 0;
}

void	c_zjump(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	process->pc = (process->carry) ? args[0] : process->pc;
}

void	c_ldi(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	int		sum;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	sum = conf->grid[args[0] + args[1]]->val;
	process->reg[args[2]] = sum;
	process->carry = (!sum) ? 1 : 0;
}

void	c_sti(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	int		sum;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	sum = conf->grid[args[1] + args[2]]->val;
	conf->grid[sum]->val = process->reg[args[0]];
	process->carry = (!sum) ? 1 : 0;
}

void	c_fork(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	//t_process	new_process;
	//int		sum;

	(void)ocp;
	(void)args;
	process = get_process_by_id(conf->first_process, pid);
	// to try !
	// new_process = t_process(mem_cpy(&process, sizeof(t_process)));
	// new_process->pc = args[0];
	
	// need to create add_elem before.
	// may similar already exist in libft
	// add_elem(conf->first_process, &new_process);
}

void	c_lld(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	process->reg[args[1]] = conf->grid[args[0]]->val;
	process->carry = (!conf->grid[args[0]]->val) ? 1 : 0;
}

void	c_lldi(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	int		sum;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	sum = conf->grid[args[0] + args[1]]->val;
	process->reg[args[2]] = sum;
	process->carry = (!sum) ? 1 : 0;
}

void	c_lfork(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;
	//t_process	new_process;
	//int		sum;

	(void)ocp;
	(void)args;
	process = get_process_by_id(conf->first_process, pid);
	// to try !
	// new_process = t_process(mem_cpy(&process, sizeof(t_process)));
	// new_process->pc = args[0];
	
	// need to create add_elem before.
	// may similar already exist in libft
	// add_elem(conf->first_process, &new_process);
}

void	c_aff(unsigned int pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	*process;

	(void)ocp;
	process = get_process_by_id(conf->first_process, pid);
	ft_printf("register[%02d] : %d\n", process->reg[args[0]]);
}
