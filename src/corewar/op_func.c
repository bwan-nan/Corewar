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

#define DRC 1
#define IND 2
#define REG 3
#define IND_MOD 512

typedef unsigned int uint;
typedef unsigned char uchar;

int	preprocess_args(uint mem_i, uchar ocp, int arg)
{
	// this function does not check error!
	// returns preprocessed arg
	// retuturns -1 if no arg

	int	result;

	if (ocp == IND)
		result = mem_i + arg % IND_MOD;
	else if (ocp == DRC)
		result = arg;
	else if (ocp == REG)
		result = arg;
	else
		result = -1;

	return (result);
}

int[4]	get_args()
{
	// first get args from memory using ocp
	// then, check they're correct
	// then, preprocess args by type
	// pseudo code:
	
	int	args[4];

	// mem_index : index of op code in mem
	// ocp : ocp
	// arg_1 : first arg after ocp, etc

	args[0] = preprocess_arg(mem_index, ocp.arg1, arg_1);
	args[1] = preprocess_arg(mem_index, ocp.arg2, arg_2);
	args[2] = preprocess_arg(mem_index, ocp.arg3, arg_3);
	args[3] = preprocess_arg(mem_index, ocp.arg4, arg_4);
	return (args);
}

void	c_live(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf)
{
	unsigned int champ_id = args[0];

	conf->champ[champ_id].nbr_live += 1;
	conf->nbr_live += 1;

	printf("function called: %s\n", "live");
	printf("%s ( %d ), a été raporter comme étant en vie.", conf->champs[champ_id], args[0]);
}

void	c_ld(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	process.reg[args[1]].val = conf->grid[args[0]].val;
	process.carry = (!conf->grid[args[0]].val) ? 1 : 0;
}

void	c_st(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	conf->grid[args[1]].val = process.reg[args[0]];
	process.carry = (!conf->grid[args[0]].val) ? 1 : 0;
}


void	c_add(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	process.reg[args[2]].val = process.reg[args[0]].val + process.reg[args[1]].val;
	process.carry = (process.reg[args[2]].val) ? 1 : 0;
}

void	c_sub(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	process.reg[args[2]].val = process.reg[args[0]].val - process.reg[args[1]].val;
	process.carry = (process.reg[args[2]].val) ? 1 : 0;
}

void	c_and(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	process.reg[args[2]].val = (process.reg[args[0]].val & process.reg[args[1]].val);
	process.carry = (process.reg[args[2]].val) ? 1 : 0;
}

void	c_or(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	process.reg[args[2]].val = (process.reg[args[0]].val | process.reg[args[1]].val);
	process.carry = (process.reg[args[2]].val) ? 1 : 0;
}

void	c_xor(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	process.reg[args[2]].val = (process.reg[args[0]].val ^ process.reg[args[1]].val);
	process.carry = (process.reg[args[2]].val) ? 1 : 0;
}

void	c_zjump(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	process.pc = (process.carry) ? args[0] : process.pc;
}

void	c_ldi(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;
	int		sum;

	process = get_process_by_id(conf->first_process, pid);
	sum = conf->grid[args[0] + args[1]].val;
	process.reg[args[2]].val = sum;
	process.carry = (!sum) ? 1 : 0;
}

void	c_sti(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;
	int		sum;

	process = get_process_by_id(conf->first_process, pid);
	sum = conf->grid[args[1] + args[2]].val;
	conf->grid[sum].val = process.reg[args[0]];
	process.carry = (!sum) ? 1 : 0;
}

void	c_fork(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;
	t_process	new_process;
	int		sum;

	process = get_process_by_id(conf->first_process, pid);
	// to try !
	new_process = t_process(mem_cpy(&process, sizeof(t_process));
	new_process.pc = args[0];
	
	// need to create add_elem before.
	// may similar already exist in libft
	add_elem(conf->first_process, &new_process);
}

void	c_lld(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;

	process = get_process_by_id(conf->first_process, pid);
	process.reg[args[1]].val = conf->grid[args[0]].val;
	process.carry = (!conf->grid[args[0]].val) ? 1 : 0;
}

void	c_lldi(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;
	int		sum;

	process = get_process_by_id(conf->first_process, pid);
	sum = conf->grid[args[0] + args[1]].val;
	process.reg[args[2]].val = sum;
	process.carry = (!sum) ? 1 : 0;
}

void	c_lfork(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	t_process	process;
	t_process	new_process;
	int		sum;

	process = get_process_by_id(conf->first_process, pid);
	// to try !
	new_process = t_process(mem_cpy(&process, sizeof(t_process));
	new_process.pc = args[0];
	
	// need to create add_elem before.
	// may similar already exist in libft
	add_elem(conf->first_process, &new_process);
}

void	c_aff(uint pid, t_ocp ocp, int args[4], t_conf *conf)
{
	ft_printf("resister[%02d] : %d\n", conf->reg[args[0]]);
}
