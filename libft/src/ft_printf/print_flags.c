/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:32:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 15:49:08 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_extra_o(t_conv *conv, int len, int *prec, int is_width)
{
	if ((!FLAG.zero || (FLAG.zero && is_width && PREC > 0))
	&& WIDTH > ft_max(*prec, len) && !FLAG.less)
		while (--WIDTH >= PREC && WIDTH >= len)
			RET += write(1, " ", 1);
	if (FLAG.sharp && *prec >= 0)
	{
		RET += write(1, "0", 1);
		--(*prec);
		*prec -= *prec == 1 ? 1 : 0;
	}
	if (WIDTH > ft_max(*prec, len) && !FLAG.less && FLAG.zero && PREC <= 0)
		while (--WIDTH >= *prec && WIDTH >= len)
			RET += write(1, "0", 1);
	if (PREC != -1 && len < PREC)
		while (--(*prec) >= len)
			RET += write(1, "0", 1);
}

void	print_extra_x(t_conv *conv, int prec, int len)
{
	if (WIDTH > ft_max(prec, len) && !FLAG.less && FLAG.zero && PREC == -1)
		while (--WIDTH >= prec && WIDTH >= len)
			RET += write(1, "0", 1);
	if (PREC != -1 && len < PREC)
		while (PREC-- > len)
			RET += write(1, "0", 1);
}

void	print_space_before(t_conv *conv, int max, char *output)
{
	if (FLAG.space && *output != '-' && TYPE != 'u')
	{
		RET += write(1, " ", 1);
		--WIDTH;
	}
	if (WIDTH > max && !FLAG.less && !(FLAG.zero && PREC == -1))
		while (--WIDTH >= max)
			RET += write(1, " ", 1);
}

void	print_space_after(t_conv *conv, int max)
{
	if (WIDTH > max && FLAG.less)
		while (--WIDTH >= max)
			RET += write(1, " ", 1);
}

void	print_zeros(t_conv *conv, int digits)
{
	int		tmp;

	tmp = PREC;
	if (tmp > digits)
		while (--tmp >= digits)
			RET += write(1, "0", 1);
}
