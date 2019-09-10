/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 23:34:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/05 12:00:29 by fdagbert         ###   ########.fr       */
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
		if (!conf->opt[4])
			ft_printf(" %.2x", conf->grid[i]->val);
		else
			ft_printf(" 00");
		i++;
		if (!(i % D_GRID_SIZE) && i != MEM_SIZE)
			ft_printf("\n%#.4x :", i);
	}
	ft_printf("\n");
}

static void		ft_refresh_grid(t_conf *conf)
{
	unsigned int	i;

	i = 0;
	if (conf->opt[5])
	{
		while (i < conf->clear)
			i++;
		if (D_CLEAR_TRICK)
			write(1, "\e[3J\e[H\e[2 ", 11);
		else
			ft_printf("{CLEAR}");
	}
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
		if (D_CLEAR_TRICK)
			ft_printf("|");
		while (i < MEM_SIZE)
		{
			ft_print_color(i, conf);
			i++;
			if (!(i % D_GRID_SIZE))
				ft_printf("|\n");
		}
		if (!conf->opt[10])
			ft_printf("\n");
	}
}
