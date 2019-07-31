/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:22:29 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/20 06:17:23 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_conv_file(t_config *conf)
{
	int		i;
	int		ret;
	int		fd;
	char	*str;

	i = 0;
	ret = 1;
	fd = (int)va_arg(conf->ap, int);
	str = D_FILE_ERR;
	ft_addbuff(conf, 0);
	while (ret > 0)
	{
		if ((ret = read(fd, conf->buff, D_BUFF_SIZE)) < 0)
		{
			while (str[i] != 0)
				ft_addbuff(conf, str[i++]);
		}
		else
			ft_addbuff(conf, 0);
	}
}
