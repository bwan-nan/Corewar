/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/19 20:03:17 by fdagbert         ###   ########.fr       */
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

static void		ft_fillstrfinal(t_config *conf, char *str)
{
	int		i;

	i = 0;
	if (conf->options[0])
	{
		while (i < conf->lenstart)
			ft_addbuff(conf, str[i++]);
		while (i++ < conf->width)
			ft_fill_opt(conf);
	}
	else
	{
		while (i++ < (conf->width - conf->lenstart))
			ft_fill_opt(conf);
		i = 0;
		while (i < conf->lenstart)
			ft_addbuff(conf, str[i++]);
	}
}

static void		ft_calc_len(t_config *conf, char *str)
{
	conf->lenraw = ft_strlen(str);
	conf->lenstart = conf->lenraw;
	conf->lenfinal = conf->lenraw;
	if (conf->accuracy > 0)
	{
		conf->lenfinal = conf->accuracy;
		if (conf->accuracy < conf->lenstart)
			conf->lenstart = conf->accuracy;
	}
	else if (conf->accuracy < 0)
	{
		conf->lenraw = 0;
		conf->lenstart = 0;
		conf->lenfinal = 0;
	}
	if (conf->width > conf->lenfinal)
		conf->lenfinal = conf->width;
	if (conf->accuracy > conf->lenfinal)
		conf->lenfinal = conf->accuracy;
}

void			ft_conv_string(t_config *conf)
{
	char	*str;

	str = NULL;
	if (conf->size == 3)
		ft_conv_wstr(conf);
	else
	{
		str = va_arg(conf->ap, char *);
		if (!str)
			str = D_SNULL;
		ft_calc_len(conf, str);
		ft_fillstrfinal(conf, str);
	}
}
