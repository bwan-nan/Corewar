/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_address.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/19 20:22:40 by fdagbert         ###   ########.fr       */
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

static int		ft_fill_accu_sharp(t_config *conf, int i, int sharp)
{
	int j;

	if (sharp)
	{
		ft_addbuff(conf, '0');
		ft_addbuff(conf, 'x');
	}
	else
	{
		j = 0;
		while (j < (conf->accuracy - conf->lenraw))
		{
			ft_addbuff(conf, '0');
			i++;
			j++;
		}
	}
	return (i);
}

static void		ft_fill_address(t_config *conf, uintmax_t address, int i)
{
	if (conf->options[0] || conf->options[2])
	{
		ft_fill_accu_sharp(conf, 0, 1);
		if (conf->accuracy > 0)
			i = ft_fill_accu_sharp(conf, i, 0);
		if (address)
			ft_umtoa_base(conf, address, 0);
		else if (conf->accuracy != -1)
			ft_addbuff(conf, '0');
		i += conf->lenraw;
		while (i++ < conf->width)
			ft_fill_opt(conf);
	}
	else
	{
		while (i++ < (conf->width - conf->lenstart))
			ft_fill_opt(conf);
		ft_fill_accu_sharp(conf, 0, 1);
		if (conf->accuracy > 0)
			i = ft_fill_accu_sharp(conf, i, 0);
		if (address)
			ft_umtoa_base(conf, address, 0);
		else if (conf->accuracy != -1)
			ft_addbuff(conf, '0');
	}
}

static void		ft_fill_pnull(t_config *conf)
{
	int		i;
	char	*strnull;

	i = 0;
	strnull = D_PNULL;
	if (conf->options[0] || conf->options[2])
	{
		while (strnull[i] != 0)
			ft_addbuff(conf, strnull[i++]);
		while (i++ < conf->width)
			ft_fill_opt(conf);
	}
	else
	{
		conf->lenraw = ft_strlen(D_PNULL);
		while (i++ < (conf->width - conf->lenraw))
			ft_fill_opt(conf);
		i = 0;
		while (strnull[i] != 0)
			ft_addbuff(conf, strnull[i++]);
	}
}

void			ft_conv_address(t_config *conf)
{
	uintmax_t	address;

	address = (uintmax_t)va_arg(conf->ap, uintptr_t *);
	ft_umtoa_base(conf, address, 1);
	conf->lenstart = conf->lenraw;
	conf->lenfinal = conf->lenraw;
	if (conf->width > conf->lenfinal)
		conf->lenfinal = conf->width;
	if (conf->accuracy > conf->lenfinal)
		conf->lenfinal = conf->accuracy;
	conf->width -= 2;
	conf->lenfinal += 2;
	if (conf->accuracy >= conf->lenstart)
		conf->lenstart += 2;
	if (address || D_PNULL[0] == '0')
		ft_fill_address(conf, address, 0);
	else
		ft_fill_pnull(conf);
}
