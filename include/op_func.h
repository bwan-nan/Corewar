/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboursal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:37:54 by jboursal          #+#    #+#             */
/*   Updated: 2019/07/19 11:16:01 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_FUNC_H
# define OP_FUNC_H

# include "corewar.h"

/*typedef struct  s_conf
{
	unsigned char memory[MEM_SIZE];
}				t_conf;*/

void	(*op_funcs[16]) (unsigned int args[4], t_conf *conf);

void	c_live(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_ld(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_st(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_add(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_sub(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_and(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_or(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_xor(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_zjump(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_ldi(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_sti(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_fork(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_lld(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_lldi(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_lfork(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);
void	c_aff(unsigned int pid, t_ocp ocp, unsigned int args[4], t_conf *conf);

#endif
