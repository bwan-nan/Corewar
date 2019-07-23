/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:34:04 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/13 03:29:08 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_arg_uint(t_config *conf, t_conv *number)
{
	if (conf->size == 0)
		number->ju = (uintmax_t)va_arg(conf->ap, unsigned int);
	else if (conf->size == 1)
		number->ju = (unsigned short)va_arg(conf->ap, unsigned int);
	else if (conf->size == 2)
		number->ju = (unsigned char)va_arg(conf->ap, unsigned int);
	else if (conf->size == 3)
		number->ju = (uintmax_t)va_arg(conf->ap, unsigned long);
	else if (conf->size == 4)
		number->ju = (uintmax_t)va_arg(conf->ap, unsigned long long);
	else if (conf->size == 5)
		number->ju = va_arg(conf->ap, uintmax_t);
	else if (conf->size == 6)
		number->ju = (uintmax_t)va_arg(conf->ap, size_t);
	ft_umtoa_base(conf, number->ju, 1);
}

static void		ft_arg_int(t_config *conf, t_conv *number)
{
	if (conf->type == 'd' || conf->type == 'D' || conf->type == 'i')
	{
		if (conf->size == 0)
			number->j = (intmax_t)va_arg(conf->ap, int);
		else if (conf->size == 1)
			number->j = (short)va_arg(conf->ap, int);
		else if (conf->size == 2)
			number->ju = (char)va_arg(conf->ap, unsigned int);
		else if (conf->size == 3)
			number->j = (intmax_t)va_arg(conf->ap, long);
		else if (conf->size == 4)
			number->j = (intmax_t)va_arg(conf->ap, long long);
		else if (conf->size == 5)
			number->j = va_arg(conf->ap, intmax_t);
		else if (conf->size == 6)
			number->j = (intmax_t)va_arg(conf->ap, size_t);
		ft_imtoa_base(conf, number->j, 1);
	}
	else
		ft_arg_uint(conf, number);
}

static void		ft_calc_len(t_config *conf, t_conv *number)
{
	if (conf->options[6])
		conf->lenraw += conf->lenraw / conf->sep;
	conf->lenfinal = conf->lenraw;
	conf->lenstart = conf->lenraw;
	if (conf->width > conf->lenfinal)
		conf->lenfinal = conf->width;
	if (conf->accuracy >= conf->lenfinal)
		conf->lenfinal = conf->accuracy + conf->neg;
	if (conf->accuracy >= conf->lenstart)
		conf->lenstart = conf->accuracy + conf->neg;
	if (((conf->options[1] || conf->options[3]) && !conf->neg)
			&& (conf->lenfinal >= conf->width))
	{
		conf->lenfinal++;
		conf->lenstart++;
	}
	if (number->j && conf->options[4] && conf->base == 16)
		conf->width -= 2;
	if (!number->j && conf->accuracy == -1
			&& (conf->base != 8 || !conf->options[4]))
	{
		conf->neg = 0;
		conf->lenraw = 0;
		conf->lenstart = 0;
	}
}

void			ft_conv_int(t_config *conf)
{
	t_conv		number;

	number.j = 0;
	ft_arg_int(conf, &number);
	ft_calc_len(conf, &number);
	if (number.j && conf->options[4] && conf->base == 16)
		conf->fsharp = 1;
	ft_fill_int(conf, &number);
}
