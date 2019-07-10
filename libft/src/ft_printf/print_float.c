/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:56:18 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 11:16:35 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_flags_before(t_conv *conv)
{
	if (FLAG.space && !SIGN)
	{
		RET += write(1, " ", 1);
		--WIDTH;
	}
	if (WIDTH > LEN + P_DIFF + SIGN && (!FLAG.zero || EDGE) && !FLAG.less)
		while (--WIDTH > LEN + P_DIFF + SIGN - EDGE)
			RET += write(1, " ", 1);
	if (SIGN)
	{
		if ((!SIZE.lf && IS_NEG) || (SIZE.lf && *FLOATS->binary == '1'))
			RET += write(1, "-", 1);
		else
			RET += write(1, "+", 1);
	}
	if (WIDTH > LEN + P_DIFF + SIGN && FLAG.zero && !FLAG.less && !EDGE)
		while (--WIDTH > LEN + P_DIFF + SIGN)
			RET += write(1, "0", 1);
}

void			print_float(t_conv *conv)
{
	if (ft_strequ(RESULT, "nan"))
	{
		PREC = 3;
		print_sp(conv, RESULT);
		return ;
	}
	print_flags_before(conv);
	RET += write(1, RESULT, LEN);
	if (FLAG.sharp && PREC == 0)
		RET += write(1, ".", 1);
	while (P_DIFF--)
		RET += write(1, "0", 1);
	if (!ft_strequ(RESULT, "inf"))
		--WIDTH;
	if (WIDTH > LEN + P_DIFF + SIGN && FLAG.less)
		while (--WIDTH > LEN + P_DIFF + SIGN)
			RET += write(1, " ", 1);
}
