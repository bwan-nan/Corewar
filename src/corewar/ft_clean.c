/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:04:43 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/17 17:39:18 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_del_players(t_conf *conf)
{
	t_champ		*temp;
	t_champ		*next;

	temp = conf->first_player;
	next = NULL;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
}

void			ft_clean(t_conf *conf)
{
	ft_del_players(conf);
}
