/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_conf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 01:54:08 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/20 20:18:38 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_check_invalid_opts(t_config *conf)
{
	if (conf->options[0] && conf->options[2])
		conf->options[2] = 0;
	if (conf->options[1] && conf->options[3])
		conf->options[3] = 0;
	if (conf->accuracy > 0 && conf->options[2])
		conf->options[2] = 0;
	if (conf->options[4] && (conf->type != 'o' && conf->type != 'O' &&
				conf->type != 'x' && conf->type != 'X' && conf->type != 'k' &&
				conf->type != '&'))
		conf->options[4] = 0;
	if ((conf->options[1] || conf->options[3]) && (conf->type == 'b' ||
				conf->type == 'u' || conf->type == 'U' || conf->type == 'o' ||
				conf->type == 'O' || conf->type == 'x' || conf->type == 'X'))
	{
		conf->options[1] = 0;
		conf->options[3] = 0;
	}
	if (conf->options[6] && (conf->type != 'b' && conf->type != 'd' &&
				conf->type != 'D' && conf->type != 'i' && conf->type != 'u' &&
				conf->type != 'U'))
		conf->options[6] = 0;
	if (conf->type == 'D' || conf->type == 'O' || conf->type == 'U' ||
			conf->type == 'C' || conf->type == 'S')
		conf->size = 3;
	return (0);
}

static int		ft_check_base_width(t_config *conf)
{
	if (conf->type == 'b')
		conf->base = 2;
	else if (conf->type == 'o' || conf->type == 'O')
		conf->base = 8;
	else if (conf->type == 'x' || conf->type == 'X' || conf->type == 'p')
		conf->base = 16;
	else
		conf->base = 10;
	if (conf->width < 0)
	{
		conf->width = -(conf->width);
		conf->options[0] = 1;
	}
	return (0);
}

int				ft_check_conf(t_config *conf)
{
	ft_check_base_width(conf);
	if (conf->type == 'b')
		conf->sep = 8;
	else
		conf->sep = 3;
	if (conf->size == 7 && conf->type != 'f')
	{
		if (D_ENABLE_L_LL)
			conf->size = 4;
		else
			conf->size = 0;
	}
	ft_check_invalid_opts(conf);
	return (0);
}
