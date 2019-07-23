/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_wild.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/19 20:00:46 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_set_wild(t_config *conf, const char *str)
{
	int		i;

	i = 1;
	if (!ft_isdigit(str[i]))
		conf->width = (int)va_arg(conf->ap, int);
	else
	{
		va_arg(conf->ap, int);
		conf->width = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
	}
	return (i);
}
