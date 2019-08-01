/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_umtoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 21:26:25 by fdagbert          #+#    #+#             */
/*   Updated: 2018/08/22 23:35:11 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		ft_printbase(int nb, t_config *conf)
{
	if (nb < 10)
		nb += '0';
	else if (conf->type == 'X')
		nb += ('A' - 10);
	else
		nb += ('a' - 10);
	return ((char)nb);
}

static void		ft_fill_str(uintmax_t nb, t_config *conf, int i)
{
	int		temp;

	if (nb > 0)
	{
		if (i < conf->sep)
			i++;
		else
			i = 1;
		temp = nb % conf->base;
		nb /= conf->base;
		ft_fill_str(nb, conf, i);
		if (conf->options[6] && i == conf->sep && nb)
			ft_addbuff(conf, D_THOUSAND_SEP);
		ft_addbuff(conf, ft_printbase(temp, conf));
	}
}

void			ft_umtoa_base(t_config *conf, uintmax_t n, int count)
{
	size_t		size;

	size = 0;
	if (count)
	{
		if (n == 0 || (conf->options[4] && conf->base == 8))
			size++;
		while (n > 0)
		{
			size++;
			n /= conf->base;
		}
		conf->lenraw = size;
	}
	else if (n == 0)
		ft_addbuff(conf, '0');
	else
	{
		if (conf->options[4] && conf->base == 8)
			ft_addbuff(conf, '0');
		ft_fill_str(n, conf, 0);
	}
}
