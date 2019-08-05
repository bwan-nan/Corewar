/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stealth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/05 10:51:44 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_print_pid(int i, t_conf *conf)
{
	if (conf->grid[i]->pid == 1)
		ft_printf("|{GRE}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 2)
		ft_printf("|{CYA}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 3)
		ft_printf("|{MAG}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 4)
		ft_printf("|{RED}00{OFF}", conf->grid[i]->val);
	else
		ft_printf("|00", conf->grid[i]->val);
}

static void		ft_print_bold(int i, t_conf *conf)
{
	if (conf->grid[i]->pid == 1)
		ft_printf("|{BOLD}{GRE}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 2)
		ft_printf("|{BOLD}{CYA}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 3)
		ft_printf("|{BOLD}{MAG}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 4)
		ft_printf("|{BOLD}{RED}00{OFF}", conf->grid[i]->val);
	else
		ft_printf("|{BOLD}00{OFF}", conf->grid[i]->val);
	conf->grid[i]->bold--;
}

static void		ft_print_invert(int i, t_conf *conf)
{
	if (conf->grid[i]->pc == 1)
		ft_printf("|{INVER}{GRE}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pc == 2)
		ft_printf("|{INVER}{CYA}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pc == 3)
		ft_printf("|{INVER}{MAG}00{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pc == 4)
		ft_printf("|{INVER}{RED}00{OFF}", conf->grid[i]->val);
	else
		ft_printf("|{INVER}00{OFF}", conf->grid[i]->val);
}

void			ft_print_stealth(int i, t_conf *conf)
{
	if (conf->grid[i]->pc)
		ft_print_invert(i, conf);
	else if (conf->grid[i]->live)
	{
		ft_printf("|{BOLD}{WHI}00{OFF}", conf->grid[i]->val);
		conf->grid[i]->live--;
	}
	else if (conf->grid[i]->bold)
		ft_print_bold(i, conf);
	else
		ft_print_pid(i, conf);
}
