/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_players.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:35:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/01 15:26:40 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_check_id_players(int id, int *id_tab, t_champ *champ,
		t_conf *conf)
{
	while (champ)
	{
		if (champ->force_id)
		{
			if (champ->force_id > MAX_PLAYERS || id_tab[champ->force_id])
				return (-24);
			id_tab[champ->force_id]++;
			champ->id = champ->force_id;
		}
		champ = champ->next;
	}
	champ = conf->first_player;
	while (champ)
	{
		while (id <= MAX_PLAYERS && id_tab[id])
			id++;
		if (!champ->force_id)
		{
			champ->id = id;
			id_tab[id]++;
		}
		champ = champ->next;
	}
	return (0);
}

static int		ft_force_id_players(t_champ *new, t_conf *conf)
{
	unsigned int	id;
	int				*id_tab;
	int				err;

	if (conf->opt[6])
		new->force_id = conf->force_id;
	id = 0;
	if (!(id_tab = (int *)malloc(sizeof(*id_tab) * (MAX_PLAYERS + 1))))
		return (-1);
	while (id <= MAX_PLAYERS)
		id_tab[id++] = 0;
	err = 0;
	if ((err = ft_check_id_players(1, id_tab, conf->first_player, conf)) < 0)
	{
		free(id_tab);
		return (err);
	}
	conf->force_id = 0;
	conf->opt[6] = 0;
	conf->check_id = 1;
	free(id_tab);
	return (0);
}

static void		ft_init_player(char *argv, t_champ *champ)
{
	champ->force_id = 0;
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

static int		ft_create_player(int err, char *argv, t_champ *champ,
		t_conf *conf)
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
	if (conf->opt[6] || conf->check_id)
	{
		if ((err = ft_force_id_players(champ, conf)) < 0)
			return (err);
	}
	return (0);
}

int				ft_check_players(char *argv, t_conf *conf)
{
	int					err;
	int					len;
	int					i;
	int					j;
	static const char	format[6] = " .cor";

	err = 0;
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
	if ((err = ft_create_player(0, argv, conf->first_player, conf)) < 0)
		return (err);
	return (0);
}
