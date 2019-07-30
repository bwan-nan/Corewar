/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:04:43 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/29 16:20:47 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_del_process(t_conf *conf)
{
	t_process	*process;
	t_process	*next;

	process = conf->first_process;
	next = NULL;
	while (process)
	{
		next = process->next;
		free(process);
		process = next;
	}
}

static void		ft_del_grid(t_conf *conf)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		free(conf->grid[i]);
		conf->grid[i] = NULL;
		i++;
	}
}

static void		ft_del_players(t_conf *conf)
{
	t_champ		*champ;
	t_champ		*next;

	champ = conf->first_player;
	next = NULL;
	while (champ)
	{
		next = champ->next;
		if (champ->fd > 2)
			close(champ->fd);
		free(champ);
		champ = next;
	}
}

void			ft_clean(t_conf *conf)
{
	ft_del_process(conf);
	ft_del_grid(conf);
	ft_del_players(conf);
}
