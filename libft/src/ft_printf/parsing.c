/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:37:41 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/27 12:58:42 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check_size(char *fmt, t_conv *conv)
{
	int i;

	i = 0;
	SIZE.hh = *fmt == 'h' && fmt[1] == 'h' ? 1 : 0;
	SIZE.h = *fmt == 'h' && fmt[1] != 'h' ? 1 : 0;
	SIZE.ll = *fmt == 'l' && fmt[1] == 'l' ? 1 : 0;
	SIZE.l = *fmt == 'l' && fmt[1] != 'l' ? 1 : 0;
	SIZE.lf = *fmt == 'L' ? 1 : 0;
	SIZE.j = *fmt == 'j' ? 1 : 0;
	if (SIZE.h || SIZE.hh || SIZE.l || SIZE.ll || SIZE.j || SIZE.lf)
		i += SIZE.hh == 1 || SIZE.ll == 1 ? 2 : 1;
	if (fmt[i] == 'o' && FLAG.sharp && PREC == -1)
		PREC = 0;
	OFFSET += i;
	return (output_handler(&fmt[i], conv));
}

static int		check_prec(char *fmt, t_conv *conv)
{
	int i;

	i = 0;
	if (fmt[i] == '.')
	{
		i++;
		PREC = ft_atoi(&fmt[i]);
		while (fmt[i] && (ft_isdigit(fmt[i]) || fmt[i] == '-'))
			i++;
	}
	OFFSET += i;
	return (check_size(&fmt[i], conv));
}

static int		check_width(char *fmt, t_conv *conv)
{
	int i;

	i = 0;
	conv->width = ft_atoi(fmt);
	while (fmt[i] && ft_isdigit(fmt[i]))
		i++;
	OFFSET += i;
	return (check_prec(&fmt[i], conv));
}

static int		is_flag(char c)
{
	return (c == ' ' || c == '#' || c == '+' || c == '-' || c == '0');
}

int				check_flags(char *fmt, t_conv *conv)
{
	int i;

	i = 0;
	while (fmt[i] && is_flag(fmt[i]))
	{
		if (fmt[i] == ' ')
			FLAG.space = 1;
		else if (fmt[i] == '#')
			FLAG.sharp = 1;
		else if (fmt[i] == '+')
			FLAG.plus = 1;
		else if (fmt[i] == '-')
			FLAG.less = 1;
		else if (fmt[i] == '0')
			FLAG.zero = 1;
		i++;
	}
	if (FLAG.plus && FLAG.space)
		FLAG.space = 0;
	OFFSET += i;
	return (check_width(&fmt[i], conv));
}
