/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:22:40 by fdagbert          #+#    #+#             */
/*   Updated: 2019/04/11 14:18:06 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_initconfig(t_config *conf)
{
	ft_bzero(conf->options, 10);
	conf->width = 0;
	conf->accuracy = 0;
	conf->size = 0;
	conf->type = 0;
	conf->base = 0;
	conf->lenraw = 0;
	conf->lenfinal = 0;
	conf->lenstart = 0;
	conf->neg = 0;
	conf->sep = 0;
	conf->fzero = 0;
	conf->fsharp = 0;
}

static int		ft_find_format(t_config *conf, const char *format, int i)
{
	int		j;

	j = 0;
	while (format[i] != '%' && format[i] != '{' && format[i] != 0)
	{
		ft_addbuff(conf, format[i++]);
		j++;
	}
	return (j);
}

static int		ft_find_effect(t_config *conf, const char *format, int i)
{
	int		j;

	j = 0;
	if (!(j = ft_text_effects(conf, format + i)))
	{
		ft_addbuff(conf, '{');
		return (1);
	}
	else
		return (j);
}

static int		ft_readformat(const char *format, t_config *conf)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (format[i] != 0)
	{
		ft_initconfig(conf);
		if (format[i] == '%')
		{
			j = ft_check_flags(conf, format + i + 1);
			if (!j)
				return (-1);
			else
				i += j;
			i++;
		}
		else if (format[i] == '{')
			i += ft_find_effect(conf, format, i);
		else
			i += ft_find_format(conf, format, i);
	}
	return (0);
}

int				ft_printf(const char *restrict format, ...)
{
	t_config	conf;

	if (!format)
		return (-1);
	ft_initconfig(&conf);
	ft_bzero(conf.buff, D_BUFF_SIZE + 1);
	conf.format = format;
	conf.ret = 0;
	conf.fd = 1;
	va_start(conf.ap, format);
	if (ft_readformat(format, &conf) == -1)
		return (0);
	ft_addbuff(&conf, 0);
	va_end(conf.ap);
	return (conf.ret);
}
