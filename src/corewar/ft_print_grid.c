/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/02 00:46:14 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_print_dump(t_conf *conf)
{
	int		i;

	i = 0;
	ft_printf("0x0000 :");
	while (i < MEM_SIZE)
	{
		ft_printf(" %.2x", conf->grid[i]->val);
		i++;
		if (!(i % D_GRID_SIZE) && i != MEM_SIZE)
			ft_printf("\n%#.4x :", i);
	}
	ft_printf("\n");
}

static void		ft_refresh_grid(t_conf *conf)
{
	int		i;

	i = 0;
	if (conf->opt[10])
	{
		while (i < 100000000)
			i++;
		if (D_CLEAR_TRICK)
			write(1, "\e[3J\e[H\e[2|", 11);
		else
			ft_printf("{CLEAR}");
	}
}

static void		ft_print_color(int i, t_conf *conf)
{
	if (conf->grid[i]->pid == 1)
		ft_printf("|{GRE}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 2)
		ft_printf("|{CYA}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 3)
		ft_printf("|{MAG}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 4)
		ft_printf("|{RED}%.2X{OFF}", conf->grid[i]->val);
	else
		ft_printf("|%.2X", conf->grid[i]->val);
}

static void		ft_print_bold(int i, t_conf *conf)
{
	if (conf->grid[i]->pid == 1)
		ft_printf("|{BOLD}{GRE}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 2)
		ft_printf("|{BOLD}{CYA}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 3)
		ft_printf("|{BOLD}{MAG}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pid == 4)
		ft_printf("|{BOLD}{RED}%.2X{OFF}", conf->grid[i]->val);
	else
		ft_printf("|{BOLD}%.2X", conf->grid[i]->val);
	conf->grid[i]->bold--;
}

static void		ft_print_invert(int i, t_conf *conf)
{
	if (conf->grid[i]->pc == 1)
		ft_printf("|{INVER}{GRE}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pc == 2)
		ft_printf("|{INVER}{CYA}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pc == 3)
		ft_printf("|{INVER}{MAG}%.2X{OFF}", conf->grid[i]->val);
	else if (conf->grid[i]->pc == 4)
		ft_printf("|{INVER}{RED}%.2X{OFF}", conf->grid[i]->val);
	else
		ft_printf("|{INVER}%.2X{OFF}", conf->grid[i]->val);
}

void			ft_print_grid(t_conf *conf)
{
	int		i;

	i = 0;
	if (conf->opt[0] && !conf->opt[8])
		ft_print_dump(conf);
	else if ((!conf->opt[0] && conf->opt[8])
		|| (conf->opt[0] && conf->cycle == conf->dump))
	{
		ft_refresh_grid(conf);
		if (!conf->opt[1])
			ft_printf("{YEL}Cycle:%u{OFF}\n", conf->cycle);
		while (i < MEM_SIZE)
		{
			if (conf->grid[i]->pc)
				ft_print_invert(i, conf);
			else if (conf->grid[i]->bold)
				ft_print_bold(i, conf);
			else
				ft_print_color(i, conf);
			i++;
			if (!(i % D_GRID_SIZE))
				ft_printf("|\n");
		}
		if (!conf->opt[10])
			ft_printf("\n");
	}
}
