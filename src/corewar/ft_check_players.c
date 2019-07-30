/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_players.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:35:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/29 16:35:08 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_init_player(char *argv, t_champ *champ)
{
	champ->path = argv;
	champ->fd = 0;
	champ->nb_live = 0;
	champ->nb_process = 0;
	champ->init_pc = 0;
	champ->inst_size = 0;
	champ->magic = 0;
	champ->padding1 = 0;
	champ->padding2 = 0;
	ft_bzero(champ->name, PROG_NAME_LENGTH + 1);
	ft_bzero(champ->comment, COMMENT_LENGTH + 1);
	ft_bzero(champ->inst, CHAMP_MAX_SIZE + 1);
	champ->next = NULL;
}

static int		ft_create_player(char *argv, t_champ *champ, t_conf *conf)
{
	if (!champ)
	{
		if (!(champ = (t_champ *)malloc(sizeof(*champ))))
			return (-1);
		conf->first_player = champ;
	}
	else
	{
		while (champ->next)
			champ = champ->next;
		if (!(champ->next = (t_champ *)malloc(sizeof(*champ))))
			return (-1);
		champ = champ->next;
	}
	champ->id = ++conf->nb_players;
	ft_init_player(argv, champ);
	return (0);
}

int				ft_check_players(char *argv, t_conf *conf)
{
	int					len;
	int					i;
	int					j;
	static const char	format[6] = " .cor";

	if ((len = ft_strlen(argv)) <= 4)
		return (-4);
	i = len - 1;
	j = 4;
	while (i && j)
	{
		if (argv[i] == format[j])
		{
			i--;
			j--;
		}
		else
			return (-4);
	}
	if (ft_create_player(argv, conf->first_player, conf) < 0)
		return (-1);
	return (0);
}
