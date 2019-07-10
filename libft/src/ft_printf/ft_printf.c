/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:10:38 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 23:31:49 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int		print_format(t_conv *conv, const char *format, int i)
{
	int		tmp;

	if (format[i] == '%')
	{
		tmp = i;
		i += check_flags((char *)&format[i + 1], conv);
		if (i == tmp - 1)
		{
			va_end(ARG);
			return (-1);
		}
		init_conv(conv);
	}
	else if (format[i] == '{' && isatty(1))
	{
		if (color_check(conv, &format[i], &i) == -1)
		{
			va_end(ARG);
			return (-1);
		}
	}
	else
		RET += write(1, &format[i], 1);
	return (i);
}

int				ft_printf(const char *format, ...)
{
	int			i;
	t_conv		conv;

	i = -1;
	va_start(conv.ap, format);
	init_conv(&conv);
	init_fp(&conv);
	while (format[++i])
	{
		i = print_format(&conv, format, i);
		if (format[i] == '\0')
			break ;
	}
	va_end(conv.ap);
	return (conv.ret);
}
