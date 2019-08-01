/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/08/30 22:59:03 by fdagbert         ###   ########.fr       */
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

static void		ft_fill_wc_buff(t_config *conf, char *byte, int nbyte)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (conf->options[0])
	{
		while (j < nbyte)
			ft_addbuff(conf, byte[j++]);
		i += nbyte;
		while (i++ < conf->width)
			ft_fill_opt(conf);
	}
	else
	{
		while (i++ < (conf->width - nbyte))
			ft_fill_opt(conf);
		while (j < nbyte)
			ft_addbuff(conf, byte[j++]);
	}
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

static void		ft_conv_wchar(t_config *conf)
{
	int			nbyte;
	char		byte[5];
	t_conv		letter;

	nbyte = 0;
	ft_bzero(byte, 5);
	letter.ju = (uintmax_t)va_arg(conf->ap, wint_t);
	ft_conv_utf8(conf, &letter, byte);
	while (byte[nbyte] != 0)
		nbyte++;
	if (!nbyte)
	{
		conf->fzero = 1;
		ft_fill_c_buff(conf, 0);
	}
	else
		ft_fill_wc_buff(conf, byte, nbyte);
}

void			ft_conv_char(t_config *conf)
{
	unsigned char	c;

	c = 0;
	if (conf->size == 3)
		ft_conv_wchar(conf);
	else
	{
		c = (unsigned char)va_arg(conf->ap, int);
		conf->lenfinal = conf->width + 1;
		if (!c)
			conf->fzero = 1;
		ft_fill_c_buff(conf, c);
	}
}
