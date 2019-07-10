/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:46:18 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 15:31:24 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_simple_binary(t_conv *conv, char **str)
{
	t_ftype	type;

	if (SIZE.l || SIZE.ll)
	{
		type.l_num = va_arg(ARG, long);
		*str = get_bits(&type.l_num, 8);
	}
	else if (SIZE.h)
	{
		type.i_num = va_arg(ARG, int);
		*str = get_bits(&type.i_num, 2);
	}
	else if (SIZE.hh)
	{
		type.i_num = va_arg(ARG, int);
		*str = get_bits(&type.i_num, 1);
	}
	else
	{
		type.i_num = va_arg(ARG, int);
		*str = get_bits(&type.i_num, 4);
	}
	if (*str == NULL)
		return (-1);
	return (0);
}

static char	*get_binary(t_conv *conv)
{
	char	*str;

	if (FLAG.sharp)
	{
		if (!(FLOATS = ft_memalloc(sizeof(t_float))))
			return (NULL);
		if (init_floats(conv) == -1)
			return (NULL);
		if (!(str = ft_strdup(FLOATS->binary)))
			return (NULL);
		del_floats(conv);
	}
	else if (get_simple_binary(conv, &str) == -1)
		return (NULL);
	if (!str)
		return (NULL);
	return (str);
}

int			handle_b(t_conv *conv)
{
	int		len;
	char	*str;

	if (!(str = get_binary(conv)))
		return (-1);
	len = ft_strlen(str);
	if (WIDTH > len)
	{
		if (!FLAG.less && !FLAG.zero)
			while (--WIDTH >= len)
				RET += write(1, " ", 1);
		else if (FLAG.zero && !FLAG.less)
			while (--WIDTH >= len)
				RET += write(1, "0", 1);
	}
	RET += write(1, str, len);
	if (WIDTH > len && FLAG.less)
		while (--WIDTH >= len)
			RET += write(1, " ", 1);
	ft_strdel(&str);
	return (0);
}
