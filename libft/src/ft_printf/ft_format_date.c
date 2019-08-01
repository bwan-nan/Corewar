/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_date.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 02:07:51 by fdagbert          #+#    #+#             */
/*   Updated: 2018/07/19 07:27:41 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*g_daysname[7][7] = {
	{"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi",
		"Samedi"},
	{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
		"Saturday"}
};
static const char	*g_monthsname[13][13] = {
	{0, "Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet",
		"Août", "Septembre", "Octobre", "Novembre", "Décembre"},
	{0, "January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December"}
};

static void		ft_fill_str(t_config *conf, int n)
{
	if (n < 10)
		ft_addbuff(conf, '0');
	ft_umtoa_base(conf, (uintmax_t)n, 0);
}

static void		ft_format_short(t_config *conf, t_time *t, int i)
{
	while (i < 3)
		ft_addbuff(conf, g_daysname[D_TIME_LANG][t->day][i++]);
	ft_addbuff(conf, '.');
	ft_addbuff(conf, ' ');
	if (D_TIME_LANG == 1)
	{
		ft_fill_str(conf, t->month);
		ft_addbuff(conf, '-');
		ft_fill_str(conf, t->total_day);
		ft_addbuff(conf, '-');
		ft_umtoa_base(conf, (uintmax_t)t->year, 0);
	}
	else
	{
		ft_fill_str(conf, t->total_day);
		ft_addbuff(conf, '/');
		ft_fill_str(conf, t->month);
		ft_addbuff(conf, '/');
		ft_umtoa_base(conf, (uintmax_t)t->year, 0);
	}
	ft_addbuff(conf, ' ');
	if (D_TIME_LANG == 1)
		ft_addbuff(conf, 'W');
	else
		ft_addbuff(conf, 'S');
}

static void		ft_format_literary(t_config *conf, t_time *t, int i, char *str)
{
	while (g_daysname[D_TIME_LANG][t->day][i] != '\0')
		ft_addbuff(conf, g_daysname[D_TIME_LANG][t->day][i++]);
	ft_addbuff(conf, ' ');
	ft_umtoa_base(conf, (uintmax_t)t->total_day, 0);
	ft_addbuff(conf, ' ');
	i = 0;
	while (g_monthsname[D_TIME_LANG][t->month][i] != '\0')
		ft_addbuff(conf, g_monthsname[D_TIME_LANG][t->month][i++]);
	ft_addbuff(conf, ' ');
	ft_umtoa_base(conf, (uintmax_t)t->year, 0);
	ft_addbuff(conf, ' ');
	ft_fill_str(conf, t->hour);
	ft_addbuff(conf, 'h');
	ft_fill_str(conf, t->minute);
	ft_addbuff(conf, 'm');
	ft_fill_str(conf, t->second);
	i = 0;
	while (str[i] != '\0')
		ft_addbuff(conf, str[i++]);
	if (D_UTC + t->summer < 0)
		ft_addbuff(conf, '-');
	else
		ft_addbuff(conf, '+');
	ft_umtoa_base(conf, (uintmax_t)(D_UTC + t->summer), 0);
	ft_addbuff(conf, ')');
}

static void		ft_format_iso8601(t_config *conf, t_time *t)
{
	ft_fill_str(conf, t->total_day);
	ft_addbuff(conf, 'T');
	ft_fill_str(conf, t->hour);
	ft_addbuff(conf, ':');
	ft_fill_str(conf, t->minute);
	ft_addbuff(conf, ':');
	ft_fill_str(conf, t->second);
	if ((D_UTC == 0 && t->summer == 0) || (D_UTC + t->summer == 0))
		ft_addbuff(conf, 'Z');
	else
	{
		if (D_UTC + t->summer < 0)
			ft_addbuff(conf, '-');
		else
			ft_addbuff(conf, '+');
		if (D_UTC + t->summer > -10 && D_UTC + t->summer < 10)
			ft_addbuff(conf, '0');
		if (D_UTC < 0)
			ft_umtoa_base(conf, -(D_UTC + t->summer), 0);
		else
			ft_umtoa_base(conf, D_UTC + t->summer, 0);
		ft_addbuff(conf, ':');
		ft_addbuff(conf, '0');
		ft_addbuff(conf, '0');
	}
}

void			ft_format_date(t_config *conf, t_time *t)
{
	if (conf->options[3])
	{
		ft_format_short(conf, t, 0);
		ft_umtoa_base(conf, (uintmax_t)t->week, 0);
		ft_addbuff(conf, ' ');
		ft_fill_str(conf, t->hour);
		ft_addbuff(conf, ':');
		ft_fill_str(conf, t->minute);
	}
	else if (conf->options[4])
		ft_format_literary(conf, t, 0, "s (UTC");
	else
	{
		ft_umtoa_base(conf, (uintmax_t)t->year, 0);
		ft_addbuff(conf, '-');
		ft_fill_str(conf, t->month);
		ft_addbuff(conf, '-');
		ft_format_iso8601(conf, t);
	}
}
