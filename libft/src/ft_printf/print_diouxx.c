/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diouxx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:44:09 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 15:48:51 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_output(t_conv *conv, char *output, int digits, int is_width)
{
	if (TYPE == 'd' || TYPE == 'i')
	{
		if (!(ft_strequ(output, "0") && PREC == 0) && *output != '-')
			RET += write(1, output, digits);
		else if (!(ft_strequ(output, "0") && PREC == 0))
			RET += write(1, output + 1, digits);
		else if (ft_strequ("0", output) && is_width && PREC == 0)
			RET += write(1, " ", 1);
	}
	else if (TYPE == 'o')
	{
		if (!(ft_strequ("0", output) && (PREC == 0 || PREC == 1)))
		{
			RET += write(1, output, ft_strlen(output));
		}
	}
	else if (TYPE == 'x' || TYPE == 'X')
	{
		if (!(ft_strequ("0", output) && PREC == 0))
			RET += write(1, output, ft_strlen(output));
		else if (ft_strequ("0", output) && is_width && PREC == 0)
			RET += write(1, " ", 1);
	}
}

void		print_di(t_conv *conv, char *output)
{
	int		len;
	int		prec;
	int		max;
	int		digits;
	int		is_width;

	is_width = WIDTH > 0 ? 1 : 0;
	prec = *output != '-' ?
		PREC + FLAG.plus : PREC + 1;
	len = *output != '-' ? ft_strlen(output)
		+ FLAG.plus : ft_strlen(output);
	max = ft_max(prec, len);
	print_space_before(conv, max, output);
	if (FLAG.plus && *output != '-')
		RET += write(1, "+", 1);
	digits = *output == '-' ? ft_strlen(output) - 1 : ft_strlen(output);
	RET += *output == '-' ? write(1, "-", 1) : 0;
	WIDTH -= TYPE == 'f' ? 1 : 0;
	if (WIDTH > max)
		if (!FLAG.less && FLAG.zero && PREC == -1)
			while (--WIDTH >= PREC && WIDTH >= len)
				RET += write(1, "0", 1);
	print_zeros(conv, digits);
	print_output(conv, output, digits, is_width);
	print_space_after(conv, max);
}

void		print_u(t_conv *conv, char *output)
{
	int		len;
	int		prec;
	int		max;
	int		digits;

	prec = *output != '-' ? PREC + FLAG.plus : PREC + 1;
	len = *output != '-' ?
		ft_strlen(output) + FLAG.plus : ft_strlen(output);
	max = ft_max(prec, len);
	print_space_before(conv, max, output);
	digits = *output == '-' ? ft_strlen(output) - 1 : ft_strlen(output);
	RET += *output == '-' ? write(1, "-", 1) : 0;
	if (WIDTH > max)
		if (!FLAG.less && FLAG.zero && PREC == -1)
			while (--WIDTH >= PREC && WIDTH >= len)
				RET += write(1, "0", 1);
	print_zeros(conv, digits);
	if (!(ft_strequ(output, "0") && PREC == 0))
	{
		if (*output != '-')
			RET += write(1, output, digits);
		else
			RET += write(1, output + 1, digits);
	}
	print_space_after(conv, max);
}

void		print_x(t_conv *conv, char *output)
{
	int		len;
	int		prec;
	int		is_width;
	int		r_len;

	is_width = WIDTH > 0 ? 1 : 0;
	prec = PREC == -1 ? PREC + FLAG.sharp * 2 : PREC;
	len = PREC == -1 ? ft_strlen(output) + FLAG.sharp * 2 : ft_strlen(output);
	r_len = PREC > (int)ft_strlen(output) ?
	PREC + FLAG.sharp * 2 : ft_strlen(output) + FLAG.sharp * 2;
	r_len -= ft_strequ(output, "0") && FLAG.sharp ? 2 : 0;
	if ((!FLAG.zero || (FLAG.zero && PREC != -1 && WIDTH != -1))
	&& WIDTH > ft_max(prec, len) && !FLAG.less)
		while (--WIDTH >= r_len)
			RET += write(1, " ", 1);
	if (FLAG.sharp && TYPE == 'x' && !ft_strequ("0", output))
		RET += write(1, "0x", 2);
	else if (FLAG.sharp && !ft_strequ("0", output))
		RET += write(1, "0X", 2);
	print_extra_x(conv, prec, len);
	print_output(conv, output, 0, is_width);
	if (WIDTH > ft_max(prec, len) && FLAG.less)
		while (--WIDTH >= prec && WIDTH >= r_len)
			RET += write(1, " ", 1);
}

void		print_o(t_conv *conv, char *output)
{
	int		len;
	int		prec;
	int		is_width;

	is_width = WIDTH > 0 ? 1 : 0;
	prec = PREC + FLAG.sharp;
	len = ft_strlen(output) + FLAG.sharp;
	len = ft_strequ(output, "0") && PREC == 0 ? 0 : len;
	len = len == 0 && FLAG.sharp ? 1 : len;
	print_extra_o(conv, len, &prec, is_width);
	print_output(conv, output, 0, is_width);
	if (WIDTH > ft_max(prec, len) && FLAG.less)
		while (--WIDTH >= PREC && WIDTH >= len)
			RET += write(1, " ", 1);
}
