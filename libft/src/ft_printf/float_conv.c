/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:18:08 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 15:23:56 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		long_double_edge_cases(t_conv *conv)
{
	if (!ft_strchr(FLOATS->exp, '0'))
	{
		ft_strdel(&RESULT);
		if (FLOATS->binary[16] == '0')
		{
			if (FLOATS->binary[17] == '0'
			&& !ft_strchr(FLOATS->binary + 18, '1'))
				RESULT = ft_strdup("inf");
			else if (FLOATS->binary[17] == '1')
				RESULT = ft_strdup("nan");
		}
		else if (FLOATS->binary[16] == '1' && FLOATS->binary[17] == '0')
		{
			if (!ft_strchr(FLOATS->binary + 18, '1'))
				RESULT = ft_strdup("inf");
			else
				RESULT = ft_strdup("nan");
		}
		else if (FLOATS->binary[16] == '1' && FLOATS->binary[17] == '1')
			RESULT = ft_strdup("nan");
		LEN = 3;
		EDGE = 1;
		return (!RESULT ? -1 : 1);
	}
	return (0);
}

static int		handle_edge_cases(t_conv *conv)
{
	if (SIZE.lf)
		return (long_double_edge_cases(conv));
	else
	{
		if (FLOATS->v_exp == FLOATS->bias + 1)
		{
			ft_strdel(&RESULT);
			if (!(ft_strchr(FLOATS->mant + 1, '1')))
				RESULT = ft_strdup("inf");
			else
				RESULT = ft_strdup("nan");
			LEN = 3;
			EDGE = 1;
			return (!RESULT ? -1 : 1);
		}
		if (FLOATS->v_exp == -FLOATS->bias && PREC == 0)
		{
			ft_strdel(&RESULT);
			RESULT = ft_strdup("0");
			LEN = 1;
			return (!RESULT ? -1 : 1);
		}
	}
	return (0);
}

char			*set_min(t_conv *conv, int exp)
{
	char	*min;
	int		i;

	min = init_str(B_SIZE, '1');
	INDEX = (B_SIZE - 1) / 2 - 1;
	LEN = 1;
	if (!min)
		return (NULL);
	i = -1;
	if (exp >= FLOATS->m_len)
		while (++i <= exp - FLOATS->m_len - 1)
			str_mult_by_two(&min, conv);
	else
	{
		while (++i < FLOATS->m_len - exp)
			str_div_by_two(&min, conv);
		INDEX = ft_strr_notchr_index(min, '0', '.');
		LEN = INDEX - ft_str_notchr_index(min, '0', '.') + 1;
	}
	return (min);
}

static int		format_result(t_conv *conv)
{
	char	*tmp;
	int		i;
	int		p_max;

	i = -1;
	while (++i < FLOATS->m_len + 1)
	{
		if (FLOATS->mant[FLOATS->m_len - i] == '1')
			str_addition(&RESULT, FLOATS->min);
		if (i != FLOATS->m_len)
			str_mult_by_two(&FLOATS->min, conv);
	}
	tmp = RESULT;
	p_max = ft_strlen(ft_strchr(RESULT, '.') + 1);
	if (PREC > p_max && (P_DIFF = PREC - p_max))
		PREC = p_max;
	if (format_float(conv, ft_str_notchr(RESULT, '0') - 1) == -1)
		return (-1);
	LEN = ft_strlen(RESULT);
	ft_strdel(&tmp);
	return (0);
}

int				handle_f(t_conv *conv)
{
	if (!(FLOATS = ft_memalloc(sizeof(t_float))))
		return (-1);
	if (init_floats(conv) == -1)
		return (-1);
	if ((!SIZE.lf && FLOATS->is_neg)
	|| (SIZE.lf && FLOATS->binary[0] == '1') || FLAG.plus)
		SIGN = 1;
	if (handle_edge_cases(conv))
	{
		print_float(conv);
		del_floats(conv);
		return (0);
	}
	if (format_result(conv) == -1)
	{
		del_floats(conv);
		return (-1);
	}
	print_float(conv);
	del_floats(conv);
	return (0);
}
