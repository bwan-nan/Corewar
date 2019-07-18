/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:04:43 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/18 01:47:47 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_del_players(t_conf *conf)
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
	ft_del_players(conf);
}
