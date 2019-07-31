/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_live_zjmp_aff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 02:42:35 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/30 14:52:32 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			c_live(t_process *process, t_conf *conf)
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
}

int			c_zjmp(t_process *process, t_conf *conf)
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
}

int			c_aff(t_process *process, t_conf *conf)
{
	int		reg1;

	(void)conf;
	reg1 = process->fct_args[0];
	if (process->ocp_splitted.arg1 != REG_CODE
			|| reg1 <= 0 || reg1 > REG_NUMBER)
		return (1);
	reg1 = process->reg[reg1 - 1];
	reg1 = reg1 % 256;
	ft_printf("%c", reg1);
	return (1);
}
