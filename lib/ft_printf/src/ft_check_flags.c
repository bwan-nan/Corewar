/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 00:50:01 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/20 08:13:21 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_types	g_types[] = {
	{"bdDiuUoOxX", &ft_conv_int},
	{"cC", &ft_conv_char},
	{"sS", &ft_conv_string},
	{"p", &ft_conv_address},
	{"%", &ft_conv_pct},
	{"k", &ft_conv_date},
	{"r", &ft_conv_ctrl},
	{"@", &ft_conv_fd},
	{"~", &ft_conv_file},
	{"&", &ft_conv_crypt},
	{NULL, NULL}
};
static const char		g_options[] = {'-', '+', '0', ' ', '#', '$', '\'', 0};
static const char		*g_sizes[] = {"h", "hh", "l", "ll", "j", "z", "L", 0};

static int		ft_set_options(t_config *conf, const char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		conf->options[i] = 0;
		i++;
	}
	i = 0;
	while (g_options[j] != 0)
	{
		if (str[i] == g_options[j])
		{
			conf->options[j]++;
			i++;
			j = -1;
		}
		j++;
	}
	return (i);
}

static int		ft_set_width_accu(t_config *conf, const char *str)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[i]))
		conf->width = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '*')
		i += ft_set_wild(conf, str + i);
	if (str[i] == '.')
	{
		i++;
		if (str[i] == '*')
			conf->accuracy = (int)va_arg(conf->ap, int);
		else
			conf->accuracy = ft_atoi(&str[i]);
		if (!conf->accuracy)
			conf->accuracy--;
		else if (conf->accuracy < 0)
			conf->accuracy = 0;
	}
	while (ft_isdigit(str[i]) || str[i] == '*')
		i++;
	return (i);
}

static int		ft_set_size(t_config *conf, const char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_sizes[j])
	{
		if (str[i] == g_sizes[j][0])
		{
			conf->size = j + 1;
			i++;
		}
		j++;
	}
	return (i);
}

static int		ft_set_type(t_config *conf, const char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[i])
		return (0);
	while (g_types[j].key && (!ft_strchr(g_types[j].key, str[i])))
		j++;
	if (g_types[j].key)
	{
		conf->type = str[i];
		ft_check_conf(conf);
		g_types[j].ft_start_conv(conf);
	}
	else
	{
		conf->type = 0;
		ft_conv_new(conf, str[i]);
	}
	i++;
	return (i);
}

int				ft_check_flags(t_config *conf, const char *str)
{
	int		i;

	i = 0;
	i += ft_set_options(conf, str + i);
	i += ft_set_width_accu(conf, str + i);
	i += ft_set_size(conf, str + i);
	if (!ft_set_type(conf, str + i))
		return (0);
	else
		return (i + 1);
}
