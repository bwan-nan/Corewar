/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:35:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/31 00:32:41 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_check_options(char *argv, const char *keys, t_conf *conf)
{
	int			i;
	int			j;

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
	if (!argv || !ft_str_is_numeric(argv))
	{
		if (opt == 0)
			return (-23);
		else if (opt == 6)
			conf->force_id = 0;
		return (1);
	}
	if (opt == 0)
		conf->dump = (unsigned int)ft_atoi(argv);
	else if (opt == 6)
		conf->force_id = (unsigned int)ft_atoi(argv);
	return (0);
}

static int		ft_check_opt_arg(int i, char **argv, t_conf *conf)
{
	int			err;

	err = 0;
	if (conf->opt[0] && i++)
	{
		if ((err = ft_check_next_arg(argv[i], 0, conf)) < 0)
			return (err);
	}
	if (conf->opt[6] && i++)
	{
		if ((err = ft_check_next_arg(argv[i], 6, conf)) < 0)
			return (err);
		if (err)
			i--;
	}
	return (i);
}

static int		ft_get_args_type(int i, char **argv, const char *keys,
		t_conf *conf)
{
	int			err;

	err = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1])
		{
			if ((err = ft_check_options(argv[i], keys, conf)) < 0)
				return (err);
			if ((i = ft_check_opt_arg(i, argv, conf)) < 0)
				return (i);
		}
		else if (argv[i][0])
		{
			if ((err = ft_check_players(argv[i], conf)) < 0)
				return (err);
		}
		i++;
	}
	return (0);
}

int				ft_check_args(int argc, char **argv, const char *keys,
		t_conf *conf)
{
	int			err;

	err = 0;
	while (err <= D_OPT_MAX)
		conf->opt[err++] = 0;
	if (argc > 1)
	{
		if ((err = ft_get_args_type(1, argv, keys, conf)) < 0)
			return (err);
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
