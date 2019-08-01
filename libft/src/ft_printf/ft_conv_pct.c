/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_pct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/08/30 23:11:18 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_fill_left(t_config *conf)
{
	int		i;

	i = 0;
	ft_addbuff(conf, '%');
	i++;
	while (i++ < conf->width)
	{
		if (conf->options[2])
			ft_addbuff(conf, '0');
		else
			ft_addbuff(conf, ' ');
	}
}

void			ft_conv_pct(t_config *conf)
{
	int		i;

	i = 0;
	if (conf->options[0])
		ft_fill_left(conf);
	else
	{
		while (i++ < (conf->width - 1))
		{
			if (conf->options[2])
				ft_addbuff(conf, '0');
			else
				ft_addbuff(conf, ' ');
		}
		ft_addbuff(conf, '%');
	}
}
