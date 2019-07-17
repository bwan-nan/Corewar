/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:35:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/17 17:58:08 by fdagbert         ###   ########.fr       */
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

static void		ft_init_conf(int i, t_conf *conf)
{
	while (i < D_OPT_MAX)
		conf->opt[i++] = 0;
	conf->cycle = 0;
	conf->cycle_to_die = CYCLE_TO_DIE;
	conf->nbr_live = 0;
	conf->nbr_check = 0;
	conf->first_player = NULL;
	i = 0;
	while (i < MAX_PLAYERS)
		conf->players[i++] = NULL;
	i = 0;
	while (i < MEM_SIZE)
		conf->grid[i++] = NULL;
	conf->op_tab = NULL;
	conf->first_process = NULL;
	conf->last_process = NULL;
}

static int		ft_options(char *argv, const char *keys, t_conf *conf)
{
	int i;
	int j;

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

static int		ft_check_options(int argc, char **argv, const char *keys,
		t_conf *conf)
{
	int i;
	int err;

	i = 0;
	err = 0;
	while (i < D_OPT_MAX)
		conf->opt[i++] = 0;
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			if (argv[i][0] == '-' && !argv[i][1])
			{
				if ((err = ft_options(argv[i], keys, conf)) < 0)
					return (err);
			}
			i++;
		}
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_conf		conf;
	int			err;
	static const char	keys[D_OPT_MAX] = {'d', 'v', 'a', 'x', 's', 'c', 'n',
		'h', 0};

	err = 0;
	ft_init_conf(0, &conf);
	if (argc < 2)
		return (ft_end(ft_print_man(&conf), &conf));
	if ((err = ft_check_options(argc, argv, keys, &conf)) < 0)
		return (ft_end(err, &conf));
	if (conf.opt[7])
		return (ft_end(ft_print_man(&conf), &conf));
	ft_init_op(&conf);
	ft_test_atoi_base();
	return (ft_end(err, &conf));
}
