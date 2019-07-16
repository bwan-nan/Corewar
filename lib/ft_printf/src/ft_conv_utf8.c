/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_utf8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:51:50 by fdagbert          #+#    #+#             */
/*   Updated: 2018/08/09 18:16:16 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_fillmask(t_config *conf, char *mask, t_conv *letter)
{
	int		i;
	int		lenraw;

	i = 35;
	lenraw = conf->lenraw;
	while (lenraw > 0)
	{
		while (mask[i] != 'x')
			i--;
		while (mask[i] == 'x' && lenraw > 0)
		{
			mask[i] = letter->ju % conf->base;
			mask[i] += '0';
			letter->ju /= conf->base;
			i--;
			lenraw--;
		}
	}
	while (i >= 0)
	{
		if (mask[i] == 'x')
			mask[i] = '0';
		i--;
	}
}

static void		ft_btochar(char *mask, char *byte)
{
	int		i;
	int		j;
	int		k;
	int		pow;
	char	result;

	i = 0;
	j = 0;
	while (i < 4)
	{
		k = 0;
		pow = 128;
		result = 0;
		while (k <= 7 && mask[j] != 0)
		{
			result += (mask[j] - '0') * pow;
			pow /= 2;
			j++;
			k++;
		}
		byte[i] = result;
		i++;
		j++;
	}
}

void			ft_conv_utf8(t_config *conf, t_conv *letter, char *byte)
{
	char					mask[36];
	static const char		pattern[4][36] = {"0xxxxxxx", "110xxxxx 10xxxxxx",
		"1110xxxx 10xxxxxx 10xxxxxx", "11110xxx 10xxxxxx 10xxxxxx 10xxxxxx"};

	ft_bzero(mask, 36);
	conf->base = 2;
	ft_umtoa_base(conf, letter->ju, 1);
	if (conf->lenraw <= 7)
		ft_memmove(mask, pattern[0], 8);
	else if (conf->lenraw <= 11)
		ft_memmove(mask, pattern[1], 17);
	else if (conf->lenraw <= 16)
		ft_memmove(mask, pattern[2], 26);
	else
		ft_memmove(mask, pattern[3], 35);
	ft_fillmask(conf, mask, letter);
	ft_btochar(mask, byte);
}
