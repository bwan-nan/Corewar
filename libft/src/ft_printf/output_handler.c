/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:03:46 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/28 14:06:36 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_undef_char(t_conv *conv, char *fmt)
{
	if (!FLAG.less && !FLAG.zero)
		while (--WIDTH > 0)
			RET += write(1, " ", 1);
	else if (FLAG.zero && !FLAG.less)
		while (--WIDTH > 0)
			RET += write(1, "0", 1);
	RET += write(1, fmt, 1);
	if (FLAG.less)
		while (--WIDTH > 0)
			RET += write(1, " ", 1);
}

static int		handle_conv(t_conv *conv)
{
	int i;

	i = 0;
	while (TYPE != conv->type[i])
		i++;
	if (conv->f[i](conv) == -1)
		return (-1);
	return (0);
}

static void		handle_percent(t_conv *conv)
{
	if (WIDTH != 0)
	{
		if (!FLAG.less && !FLAG.zero)
			while (--WIDTH)
				RET += write(1, " ", 1);
		else if (FLAG.zero && !FLAG.less)
			while (--WIDTH)
				RET += write(1, "0", 1);
	}
	RET += write(1, "%", 1);
	if (WIDTH != 0)
		if (FLAG.less)
			while (--WIDTH)
				RET += write(1, " ", 1);
}

int				output_handler(char *fmt, t_conv *conv)
{
	if (ft_strchr(OPTIONS, *fmt) && *fmt)
	{
		TYPE = *fmt;
		if (handle_conv(conv) == -1)
			return (-1);
		if (PREC > 0 && TYPE != 'f')
			FLAG.zero = 0;
		else if (PREC < -1)
			PREC = 0;
	}
	else if (*fmt == '%')
		handle_percent(conv);
	else if (*fmt)
		print_undef_char(conv, fmt);
	else if (!(*fmt))
		return (0);
	return (OFFSET + 1);
}
