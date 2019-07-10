/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_csp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:59:56 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 11:29:29 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_sp(t_conv *conv, char *output)
{
	int		len;
	int		i;

	len = ft_strlen(output);
	if (PREC != -1 && PREC < len)
	{
		i = TYPE == 'p' ? (int)PREC + 2 : (int)PREC;
		output[i] = '\0';
		len = ft_strlen(output);
	}
	if (WIDTH > len)
	{
		if (!FLAG.less && !FLAG.zero)
			while (--WIDTH >= len)
				RET += write(1, " ", 1);
		else if (FLAG.zero && !FLAG.less)
			while (--WIDTH >= len)
				RET += write(1, "0", 1);
	}
	RET += write(1, output, len);
	if (WIDTH > len)
		if (FLAG.less)
			while (--WIDTH >= len)
				RET += write(1, " ", 1);
}

int			print_c(t_conv *conv)
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
	ft_putchar(va_arg(ARG, int));
	RET++;
	if (WIDTH != 0)
		if (FLAG.less)
			while (--WIDTH)
				RET += write(1, " ", 1);
	return (0);
}

int			handle_p(t_conv *conv)
{
	char	*str;
	char	*tmp;

	if (!(str = ft_ullitoa_base((uintptr_t)va_arg(ARG, void *), 16)))
		return (-1);
	tmp = str;
	if (!(str = ft_strjoin("0x", str)))
	{
		ft_strdel(&tmp);
		return (-1);
	}
	ft_strdel(&tmp);
	print_sp(conv, str);
	ft_strdel(&str);
	return (0);
}

int			handle_s(t_conv *conv)
{
	char	*str;
	char	*tmp;

	tmp = va_arg(ARG, char *);
	if (tmp)
	{
		if (!(str = ft_strdup(tmp)))
			return (-1);
		print_sp(conv, str);
		ft_strdel(&str);
	}
	else
	{
		tmp = ft_strdup("(null)");
		print_sp(conv, tmp);
		ft_strdel(&tmp);
	}
	return (0);
}
