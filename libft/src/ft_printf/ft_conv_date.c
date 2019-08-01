/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_date.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 02:07:51 by fdagbert          #+#    #+#             */
/*   Updated: 2018/08/09 18:15:27 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_find_leap_year(time_t year)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return (1);
	else
		return (0);
}

static void		ft_calc_time(t_time *t, time_t timestamp)
{
	t->hour = timestamp % 86400 / 3600;
	t->minute = (timestamp % 86400 % 3600) / 60;
	t->second = timestamp % 86400 % 60;
	t->total_day = timestamp / 86400;
	t->year = D_EPOCH;
	t->leap = ft_find_leap_year(t->year);
	t->summer = 0;
	if (D_UTC)
	{
		t->hour += D_UTC;
		if (t->hour > 23)
		{
			t->hour = t->hour - 24;
			t->total_day++;
		}
		else if (t->hour < 0)
		{
			t->hour = t->hour + 24;
			t->total_day--;
		}
	}
}

static void		ft_calc_date(t_time *t, int c, int a, int m)
{
	static const int	daysbymonth[] = {
		0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	while (t->total_day >= 365 + t->leap)
	{
		t->total_day -= 365 + t->leap;
		t->year++;
		t->leap = ft_find_leap_year(t->year);
	}
	t->week = t->total_day / 7 + 1;
	t->month = 1;
	while (t->total_day >= daysbymonth[t->month])
	{
		t->total_day -= daysbymonth[t->month];
		if (t->leap && t->month == 2)
			t->total_day -= 1;
		t->month++;
	}
	t->total_day++;
	c = (14 - t->month) / 12;
	a = t->year - c;
	m = t->month + 12 * c - 2;
	t->day = (t->total_day + a + a / 4 - a / 100 + a / 400 + (31 * m) / 12) % 7;
}

static void		ft_calc_dst(t_time *t, time_t timestamp)
{
	if (D_ENABLE_DST == 1 && ((t->month > 3 && t->month < 10) ||
				(t->month == 3 && (31 - t->total_day < 7) && t->hour >= 2) ||
				(t->month == 10 && (31 - t->total_day > 7) && t->hour < 3)))
	{
		t->hour += D_HEMISP_SIDE;
		t->summer += D_HEMISP_SIDE;
		if (t->hour > 23 || t->hour < 0)
		{
			ft_calc_time(t, timestamp + (D_HEMISP_SIDE * 3600));
			ft_calc_date(t, 0, 0, 0);
			t->summer += D_HEMISP_SIDE;
		}
	}
}

void			ft_conv_date(t_config *conf)
{
	t_time				t;
	time_t				timestamp;

	timestamp = va_arg(conf->ap, time_t);
	ft_calc_time(&t, timestamp);
	ft_calc_date(&t, 0, 0, 0);
	ft_calc_dst(&t, timestamp);
	ft_format_date(conf, &t);
}
