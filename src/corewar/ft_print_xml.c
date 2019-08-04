/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xml.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/03 14:43:41 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_xml_players(t_conf *conf)
{
	unsigned int	i;

	i = 1;
	ft_printf("<corewar>\n<players>");
	while (i <= conf->nb_players)
	{
		ft_printf("<player id=\"%u\" name=\"%s\" nb_live=\"%u\"/>", i,
				conf->players[i]->name, conf->players[i]->nb_live);
		i++;
	}
}

static void		ft_xml_arena(t_conf *conf)
{
	unsigned int	i;

	i = 0;
	ft_printf("</players><arena cycle=\"%u\" cycle_die=\"%u\" \
			nb_check=\"%u\" nb_live=\"%u\" period=\"%u\"><memory size=\"%u\">",
			conf->cycle, conf->cycle_to_die, conf->nb_check,
			conf->nb_live, conf->period, MEM_SIZE);
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x,%d,", conf->grid[i]->val, conf->grid[i]->pid);
		i++;
	}
	ft_printf("</memory></arena><processes to_print=\"%u\">", conf->nb_process);
}

static void		ft_xml_registers(t_process *process)
{
	unsigned int	i;

	i = 0;
	while (i < REG_NUMBER)
	{
		ft_printf("r%u=\"%x\" ", i + 1, process->reg[i]);
		i++;
	}
	ft_printf("/></process>");
}

static void		ft_print_fct_args(t_process *process, t_conf *conf)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (((char *)(&process->ocp_splitted))[i] == 1)
			ft_printf("<byte size=\"1\" type=\"register\" value=\"%x\"/> ",
					process->fct_args[i]);
		else if (((char *)(&process->ocp_splitted))[i] == 2
				&& process->op_code < D_OP_MAX)
			ft_printf("<byte size=\"%d\" type=\"direct\" value=\"%x\"/> ",
					conf->op_tab[process->op_code].dir_size,
					process->fct_args[i]);
		else if (((char *)(&process->ocp_splitted))[i] == 2)
			ft_printf("<byte size=\"0\" type=\"direct\" value=\"0\"/> ");
		else if (((char *)(&process->ocp_splitted))[i] == 3)
			ft_printf("<byte size=\"2\" type=\"indirect\" value=\"%x\"/> ",
					process->fct_args[i]);
		else
			ft_printf("<byte size=\"0\" type=\"register\" value=\"0\"/> ");
		i++;
	}
}

static void		ft_xml_processes(t_conf *conf)
{
	t_process		*process;

	process = conf->first_process;
	while (process)
	{
		ft_printf("<process carry=\"%u\" cycle_wait=\"%u\" player_id=\"%u\" \
				process_id=\"%u\" nb_live=\"%u\" ><current_action pos=\"%u\">",
				process->carry, process->cycle_to_wait, process->id_champ,
				process->id_proc, process->nb_live, process->pc);
		if (process->op_code < D_OP_MAX)
			ft_printf("<byte size=\"%d\" type=\"ocp\" value=\"%llx\"/> ",
					conf->op_tab[process->op_code].ocp, process->ocp);
		else
			ft_printf("<byte size=\"0\" type=\"ocp\" value=\"0\"/> ");
		ft_printf("<byte size=\"1\" type=\"op\" value=\"%d\"/> ",
				process->op_code);
		ft_print_fct_args(process, conf);
		ft_printf("</current_action><registers ");
		ft_xml_registers(process);
		process = process->next;
	}
	ft_printf("</processes>\n</corewar>\n");
}

void			ft_print_xml(t_conf *conf)
{
	ft_xml_players(conf);
	ft_xml_arena(conf);
	ft_xml_processes(conf);
}
