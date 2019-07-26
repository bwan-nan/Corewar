/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:16:02 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/13 03:29:56 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_fill_accu(t_config *conf)
{
	int i;
	int j;

	i = 0;
	if (conf->accuracy > 0)
	{
		j = conf->sep - ((conf->accuracy + conf->neg) % conf->sep);
		while (i++ < (conf->accuracy - conf->lenraw + conf->neg))
		{
			if (conf->options[6] && D_ENABLE_SEP_ACCU)
			{
				if (j < conf->sep)
					j++;
				else
				{
					j = 1;
					ft_addbuff(conf, D_THOUSAND_SEP);
				}
			}
			ft_addbuff(conf, '0');
		}
	}
}

static void		ft_fill_sign_sharp(t_config *conf)
{
	if (conf->options[1] && !conf->neg)
		ft_addbuff(conf, '+');
	else if (conf->options[3] && !conf->neg)
		ft_addbuff(conf, ' ');
	else if (conf->neg)
		ft_addbuff(conf, '-');
	if (conf->fsharp == 1)
	{
		ft_addbuff(conf, '0');
		if (conf->type == 'X')
			ft_addbuff(conf, 'X');
		else
			ft_addbuff(conf, 'x');
	}
	ft_fill_accu(conf);
}

static void		ft_fill_space(t_config *conf)
{
	int i;

	i = 0;
	if (conf->options[2])
	{
		while (i++ < (conf->width - conf->lenstart))
			ft_addbuff(conf, '0');
	}
	else
	{
		while (i++ < (conf->width - conf->lenstart))
			ft_addbuff(conf, ' ');
	}
}

static void		ft_fill_left(t_config *conf, t_conv *number)
{
	ft_fill_sign_sharp(conf);
	if (conf->neg)
		ft_imtoa_base(conf, number->j, 0);
	else if (conf->lenraw)
		ft_umtoa_base(conf, number->ju, 0);
	ft_fill_space(conf);
}

void			ft_fill_int(t_config *conf, t_conv *number)
{
	if (conf->options[0])
		ft_fill_left(conf, number);
	else
	{
		if (conf->options[2])
		{
			ft_fill_sign_sharp(conf);
			ft_fill_space(conf);
		}
		else
		{
			ft_fill_space(conf);
			ft_fill_sign_sharp(conf);
		}
		if (conf->neg)
			ft_imtoa_base(conf, number->j, 0);
		else if (conf->lenraw)
			ft_umtoa_base(conf, number->ju, 0);
	}
}
