/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   date_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:46:31 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/27 12:47:35 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <time.h>

static void		print_timestamp(t_conv *conv, char *timestamp)
{
	int		len;

	len = ft_strlen(timestamp);
	if (WIDTH > len)
	{
		if (!FLAG.less && !FLAG.zero)
			while (--WIDTH >= len)
				RET += write(1, " ", 1);
		else if (FLAG.zero && !FLAG.less)
			while (--WIDTH >= len)
				RET += write(1, "0", 1);
	}
	RET += write(1, timestamp, len);
	if (WIDTH > len && FLAG.less)
		while (--WIDTH >= len)
			RET += write(1, " ", 1);
}

static void		print_date(t_conv *conv, char *full_date, int len)
{
	if (FLAG.sharp && PREC != 4)
		RET += write(1, full_date + 4, len);
	else if (FLAG.sharp && PREC == 4)
		RET += write(1, full_date + 20, len);
	else
		RET += write(1, full_date, len);
}

int				timestamp_to_date(t_conv *conv)
{
	char	*full_date;
	time_t	timestamp;
	int		len;

	timestamp = va_arg(ARG, time_t);
	full_date = ctime(&timestamp);
	len = ft_strlen(full_date);
	len = FLAG.sharp ? 12 : len - 1;
	len = FLAG.sharp && PREC == 4 ? 4 : len;
	len = FLAG.sharp && PREC == 3 ? 3 : len;
	if (WIDTH > len)
	{
		if (!FLAG.less && !FLAG.zero)
			while (--WIDTH >= len)
				RET += write(1, " ", 1);
		else if (FLAG.zero && !FLAG.less)
			while (--WIDTH >= len)
				RET += write(1, "0", 1);
	}
	print_date(conv, full_date, len);
	if (WIDTH > len && FLAG.less)
		while (--WIDTH >= len)
			RET += write(1, " ", 1);
	return (0);
}

int				date_to_timestamp(t_conv *conv)
{
	struct tm	*time_pointer;
	char		*full_date;
	char		*time_gmt1;

	if (!(time_gmt1 = ft_strnew(256)))
		return (-1);
	if (!(time_pointer = ft_memalloc(sizeof(struct tm))))
	{
		ft_strdel(&time_gmt1);
		return (-1);
	}
	full_date = va_arg(ARG, char *);
	strptime(full_date, "%b  %d %H:%M:%S %Y", time_pointer);
	strftime(time_gmt1, 256, "%s", time_pointer);
	ft_memdel((void **)&time_pointer);
	print_timestamp(conv, time_gmt1);
	ft_strdel(&time_gmt1);
	return (0);
}
