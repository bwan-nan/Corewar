/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_wstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 01:12:03 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/19 20:08:12 by fdagbert         ###   ########.fr       */
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

static int		ft_fillstrbyte(t_config *conf, wchar_t *str, int i, int bypass)
{
	int			j;
	int			k;
	int			nbyte;
	char		byte[5];
	t_conv		letter;

	j = 0;
	while (str[j] != 0)
	{
		k = 0;
		nbyte = 0;
		ft_bzero(byte, 5);
		letter.ju = (uintmax_t)str[j];
		ft_conv_utf8(conf, &letter, byte);
		while (byte[nbyte] != 0)
			nbyte++;
		if (i + nbyte > conf->lenstart)
			return (i);
		while ((k < nbyte) && !bypass)
			ft_addbuff(conf, byte[k++]);
		i += nbyte;
		j++;
	}
	return (i);
}

static void		ft_fillstrfinal(t_config *conf, wchar_t *newstr)
{
	int		i;

	i = 0;
	if (conf->options[0])
	{
		i = ft_fillstrbyte(conf, newstr, i, 0);
		while (i < conf->width)
		{
			ft_fill_opt(conf);
			i++;
		}
	}
	else
	{
		conf->lenstart = ft_fillstrbyte(conf, newstr, i, 1);
		while (i < (conf->width - conf->lenstart))
		{
			ft_fill_opt(conf);
			i++;
		}
		conf->lenstart = conf->lenfinal;
		i = ft_fillstrbyte(conf, newstr, i, 0);
	}
}

static void		ft_calc_len(t_config *conf, wchar_t *newstr)
{
	conf->lenraw = ft_wcslen(newstr);
	conf->lenstart = conf->lenraw * 4;
	conf->lenfinal = conf->lenraw * 4;
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

void			ft_conv_wstr(t_config *conf)
{
	wchar_t			*newstr;

	newstr = NULL;
	newstr = va_arg(conf->ap, wchar_t *);
	if (!newstr)
		newstr = D_WSNULL;
	ft_calc_len(conf, newstr);
	ft_fillstrfinal(conf, newstr);
}
