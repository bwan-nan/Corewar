/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/03 22:08:08 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_fill_opt(t_config *conf)
{
	if (conf->options[2])
		ft_addbuff(conf, '0');
	else
		ft_addbuff(conf, ' ');
}

static void		ft_fill_c_buff(t_config *conf, unsigned char c)
{
	int		i;

	i = 0;
	if (conf->options[0])
	{
		ft_addbuff(conf, c);
		i++;
		while (i < conf->width)
		{
			ft_fill_opt(conf);
			i++;
		}
	}
	else
	{
		while (i < (conf->width - 1))
		{
			ft_fill_opt(conf);
			i++;
		}
		ft_addbuff(conf, c);
	}
}

void			ft_conv_new(t_config *conf, unsigned char c)
{
	conf->lenfinal = conf->width;
	ft_fill_c_buff(conf, c);
}
