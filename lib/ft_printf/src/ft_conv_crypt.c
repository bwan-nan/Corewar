/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_crypt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/19 20:36:07 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_decrypt_str(t_config *conf, char *str)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	j = 0;
	c = 0;
	while (str[i] != 0)
	{
		if (str[i] >= 32 && str[i] < 127)
		{
			c = str[i] - D_CRYPT_KEY[j];
			while (c < 32)
				c = (c + 127) - 32;
			ft_addbuff(conf, c);
			j++;
			if (!D_CRYPT_KEY[j])
				j = 0;
		}
		else
			ft_addbuff(conf, str[i]);
		i++;
	}
}

static void		ft_crypt_str(t_config *conf, char *str)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	j = 0;
	c = 0;
	while (str[i] != 0)
	{
		if (str[i] >= 32 && str[i] < 127)
		{
			c = str[i] + D_CRYPT_KEY[j];
			while (c >= 127)
				c = (c - 127) + 32;
			ft_addbuff(conf, c);
			j++;
			if (!D_CRYPT_KEY[j])
				j = 0;
		}
		else
			ft_addbuff(conf, str[i]);
		i++;
	}
}

void			ft_conv_crypt(t_config *conf)
{
	char	*str;

	str = NULL;
	str = va_arg(conf->ap, char *);
	if (!str)
		str = D_SNULL;
	if (conf->options[4])
		ft_decrypt_str(conf, str);
	else
		ft_crypt_str(conf, str);
}
