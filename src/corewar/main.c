/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:35:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/24 21:43:32 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


static int		ft_print_man(t_conf *conf)
{
	int		fd;

	fd = 0;
	if ((fd = open(D_MAN_PATH, O_RDONLY)) < 0)
		return (-22);
	ft_printf("##VISUOFF\n");
	if (conf->opt[5])
		ft_printf("{GRE}%~{OFF}\n", fd);
	else
		ft_printf("%~\n", fd);
	if (close(fd) < 0)
		return (-22);
	return (0);
}

static void			op_funcs_init(t_conf *conf) //added
{
	conf->op_funcs[0] = c_live;  //added
	conf->op_funcs[1] = c_ld;  //added
	conf->op_funcs[2] = c_st;  //added
	conf->op_funcs[3] = c_add;  //added
	conf->op_funcs[4] = c_sub;  //added
	conf->op_funcs[5] = c_and;  //added
	conf->op_funcs[6] = c_or;  //added
	conf->op_funcs[7] = c_xor;  //added
	conf->op_funcs[8] = c_zjump;  //added
	conf->op_funcs[9] = c_ldi;  //added
	conf->op_funcs[10] = c_sti;  //added
	conf->op_funcs[11] = c_fork;  //added
	conf->op_funcs[12] = c_lld;  //added
	conf->op_funcs[13] = c_lldi;  //added
	conf->op_funcs[14] = c_lfork;  //added
	conf->op_funcs[15] = c_aff;  //added
}

static void		ft_init_conf(int i, t_conf *conf)
{
	conf->dump = 0;
	conf->nb_player = 0;
	conf->nb_process = 0;
	conf->total_process = 0;
	conf->nb_live = 0;
	conf->last_live = 0;
	conf->nb_check = 0;
	conf->cycle = 0;
	conf->cycle_to_die = CYCLE_TO_DIE;
	conf->period = 0;
	conf->first_player = NULL;
	i = 0;
	while (i <= MAX_PLAYERS)
		conf->players[i++] = NULL;
	i = 0;
	while (i < MEM_SIZE)
		conf->grid[i++] = NULL;
	conf->op_tab = NULL;
	conf->first_process = NULL;
	op_funcs_init(conf);
}

static int		ft_check_options(char *argv, const char *keys, t_conf *conf)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (keys[i])
	{
		if (argv[j] && argv[j] == keys[i])
		{
			if (!conf->opt[i])
				conf->opt[i] = 1;
			else
				return (-21);
			j++;
			if (!argv[j])
				return (0);
			i = -1;
		}
		i++;
	}
	return (-20);
}

static int		ft_check_next_arg(char *argv, int opt, t_conf *conf)
{
	if (opt == 0)
	{
		if (!argv)
			return (-23);
		if (!ft_str_is_numeric(argv))
			return (-23);
		conf->dump = (unsigned int)ft_atoi(argv);
	}
	return (0);
}

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
	champ->id = ++conf->nb_player;
	ft_init_player(argv, champ);
	return (0);
}

static int		ft_check_players(char *argv, t_conf *conf)
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

static int		ft_check_args(int argc, char **argv, const char *keys,
		t_conf *conf)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (i <= D_OPT_MAX)
		conf->opt[i++] = 0;
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			if (argv[i][0] == '-' && argv[i][1])
			{
				if ((err = ft_check_options(argv[i], keys, conf)) < 0)
					return (err);
				if (conf->opt[0])
				{
					i++;
					if ((err = ft_check_next_arg(argv[i], 0, conf)) < 0)
						return (err);
				}
			}
			else if (argv[i][0])
			{
				if ((err = ft_check_players(argv[i], conf)) < 0)
					return (err);
			}
			i++;
		}
	}
	else
		return (1);
	if (conf->opt[3])
	{
		conf->opt[1] = 0;
		conf->opt[2] = 0;
		conf->opt[4] = 0;
		conf->opt[9] = 0;
	}
	return (0);
}

static int		ft_init_fd(t_champ *champ, t_conf *conf)
{
	while (champ)
	{
		if ((champ->fd = open(champ->path, O_RDONLY)) < 0)
			return (-2);
		conf->players[champ->id] = champ;
		champ = champ->next;
	}
	if (!conf->nb_player)
		return (-5);
	if (conf->nb_player > MAX_PLAYERS)
		return (-6);
	return (0);
}

static int		ft_check_define(void)
{
	int		int_size;

	int_size = sizeof(int);
	if (REG_SIZE != int_size)
	{
		if (int_size == 4)
			return (-7);
		else if (int_size == 8)
			return (-8);
		else
			return (-9);
	}
	return (0);
}

static void		ft_print_winner(t_conf *conf)
{
	if (!conf->opt[0])
	{
		if (!(conf->last_live))
			ft_printf("Il n'y a pas de survivant...\n");
		else
			ft_printf("Le joueur %d(%s) a gagné !\n", conf->last_live, conf->players[conf->last_live]->name);
	}
}

int				main(int argc, char **argv)
{
	int					err;
	t_conf				conf;
	static const char	keys[D_OPT_MAX + 1] = {'d', 'v', 'a', 'x', 's', 'c',
		'n', 'h', 'b', 'e', 'm', 0};

	err = 0;
	ft_init_conf(0, &conf);
	if ((err = ft_check_args(argc, argv, keys, &conf)) < 0)
		return (ft_end(err, &conf));
	if (conf.opt[7] || err == 1)
		return (ft_end(ft_print_man(&conf), &conf));
	if ((err = ft_init_fd(conf.first_player, &conf)) < 0)
		return (ft_end(err, &conf));
	if ((err = ft_check_define()) < 0)
		return (ft_end(err, &conf));
	ft_init_op(&conf);
	if ((err = ft_champion_parser(conf.first_player, &conf)) < 0)
		return (ft_end(err, &conf));
	if ((err = ft_init_arena(conf.first_player, &conf)) < 0)
		return (ft_end(err, &conf));
	if ((err = ft_launch_arena(conf.first_process, &conf)) < 0)
		return (ft_end(err, &conf));
	if (!conf.opt[3])
		ft_print_winner(&conf);
	return (ft_end(err, &conf));
}
