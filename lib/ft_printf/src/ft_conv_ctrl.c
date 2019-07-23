/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/19 20:26:59 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*g_nonprintable[] = {
	"[NUL]", "[SOH]", "[STX]", "[ETX]", "[EOT]", "[ENQ]",
	"[ACK]", "[BEL]", "[BS]", "[TAB]", "[LF]", "[VT]", "[FF]",
	"[CR]", "[SO]", "[SI]", "[DLE]", "[DC1]", "[DC2]", "[DC3]",
	"[DC4]", "[NAK]", "[SYN]", "[ETB]", "[CAN]", "[EM]",
	"[SUB]", "[ESC]", "[FS]", "[GS]", "[RS]", "[US]", "[DEL]"
};

static void		ft_fill_ctrl(t_config *conf, int c)
{
	int		j;

	j = 0;
	if (c == 127)
	{
		while (g_nonprintable[32][j] != '\0')
			ft_addbuff(conf, g_nonprintable[32][j++]);
	}
	else
	{
		while (g_nonprintable[c][j] != '\0')
			ft_addbuff(conf, g_nonprintable[c][j++]);
	}
}

static int		ft_fill_left(t_config *conf, char *str, int i)
{
	while (i < conf->lenstart)
	{
		if (str[i] <= 31 || str[i] == 127)
			ft_fill_ctrl(conf, str[i++]);
		else
			ft_addbuff(conf, str[i++]);
	}
	while (i < conf->width)
	{
		ft_addbuff(conf, ' ');
		i++;
	}
	return (i);
}

static void		ft_fillstrfinal(t_config *conf, char *str, int i)
{
	if (conf->options[0])
		i = ft_fill_left(conf, str, i);
	else
	{
		while (i++ < (conf->width - conf->lenstart))
			ft_addbuff(conf, ' ');
		i = 0;
		while (i < conf->lenstart)
		{
			if (str[i] <= 31 || str[i] == 127)
				ft_fill_ctrl(conf, str[i++]);
			else
				ft_addbuff(conf, str[i++]);
		}
	}
	ft_fill_ctrl(conf, 0);
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
		conf->width = 0;
		conf->lenraw = 0;
		conf->lenstart = 0;
		conf->lenfinal = 0;
	}
	if (conf->width > conf->lenfinal)
		conf->lenfinal = conf->width;
	if (conf->accuracy > conf->lenfinal)
		conf->lenfinal = conf->accuracy;
}

void			ft_conv_ctrl(t_config *conf)
{
	char	*str;

	str = NULL;
	str = va_arg(conf->ap, char *);
	if (!str || conf->size == 3)
		str = D_SNULL;
	ft_calc_len(conf, str);
	ft_fillstrfinal(conf, str, 0);
}
