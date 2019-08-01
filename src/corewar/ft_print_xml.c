/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xml.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/31 16:48:59 by fdagbert         ###   ########.fr       */
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
		ft_printf("<player id=\"%u\" name=\"%s\" />", i,
				conf->players[i]->name);
		i++;
	}
}

static void		ft_xml_arena(t_conf *conf)
{
	unsigned int	i;

	i = 0;
	ft_printf("</players><arena cycle=\"%u\" period=\"%u\" cycle_die=\"%u\" \
			nb_check=\"%u\" nb_live=\"%u\"><memory size=\"%u\">",
			conf->cycle, conf->period, conf->cycle_to_die, conf->nb_check,
			conf->nb_live, MEM_SIZE);
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x,%d,", conf->grid[i]->val, conf->grid[i]->pid);
		i++;
	}
	ft_printf("</memory></arena><processes>");
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

static void		ft_xml_processes(t_conf *conf)
{
	t_process		*process;

	process = conf->first_process;
	while (process)
	{
		ft_printf("<process player_id=\"%u\" process_id=\"%u\" nb_live=\"%u\" \
				carry=\"%u\" cycle_wait=\"%u\"><current_action pos=\"%u\">\
				<byte size=\"1\" type=\"op\" value=\"%llx\"/><byte size=\"%d\" \
				type=\"ocp\" value=\"%llx\"/><byte size=\"%d\" type=\"direct\" \
				value=\"0\"/><byte size=\"2\" type=\"indirect\" value=\"0\"\
				/><byte size=\"%d\" type=\"register\" value=\"0\"/>\
				</current_action><registers ",
				process->id_champ, process->id_proc, process->nb_live,
				process->carry, process->cycle_to_wait, process->pc,
				process->op_code, conf->op_tab[process->op_code].ocp,
				process->ocp, conf->op_tab[process->op_code].dir_size);
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
