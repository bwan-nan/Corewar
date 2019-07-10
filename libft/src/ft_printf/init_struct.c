/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:20:17 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/27 12:59:03 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			init_conv(t_conv *conv)
{
	SIZE.h = 0;
	SIZE.hh = 0;
	SIZE.l = 0;
	SIZE.ll = 0;
	SIZE.j = 0;
	SIZE.lf = 0;
	OFFSET = 0;
	PREC = -1;
	WIDTH = -1;
	FLAG.zero = 0;
	FLAG.space = 0;
	FLAG.sharp = 0;
	FLAG.plus = 0;
	FLAG.less = 0;
	STYLE = NULL;
}

static void		init_types(t_conv *conv)
{
	conv->type[0] = 'c';
	conv->type[1] = 's';
	conv->type[2] = 'p';
	conv->type[3] = 'd';
	conv->type[4] = 'i';
	conv->type[5] = 'o';
	conv->type[6] = 'u';
	conv->type[7] = 'x';
	conv->type[8] = 'X';
	conv->type[9] = 'f';
	conv->type[10] = 'b';
	conv->type[11] = 'k';
	conv->type[12] = 'K';
}

void			init_fp(t_conv *conv)
{
	RET = 0;
	init_types(conv);
	conv->f[0] = print_c;
	conv->f[1] = handle_s;
	conv->f[2] = handle_p;
	conv->f[3] = handle_di;
	conv->f[4] = handle_di;
	conv->f[5] = handle_o;
	conv->f[6] = handle_u;
	conv->f[7] = handle_xx;
	conv->f[8] = handle_xx;
	conv->f[9] = handle_f;
	conv->f[10] = handle_b;
	conv->f[11] = timestamp_to_date;
	conv->f[12] = date_to_timestamp;
}
