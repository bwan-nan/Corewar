/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addbuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 00:16:18 by fdagbert          #+#    #+#             */
/*   Updated: 2019/04/01 21:55:56 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_printbuff(t_config *conf, size_t size)
{
	write(conf->fd, conf->buff, size);
	ft_bzero(conf->buff, D_BUFF_SIZE + 1);
	conf->ret += size;
}

void			ft_addbuff(t_config *conf, char c)
{
	size_t		size;

	size = ft_strlen(conf->buff);
	if (c)
	{
		if (size + 1 >= D_BUFF_SIZE)
		{
			ft_printbuff(conf, size);
			size = 0;
		}
		conf->buff[size] = c;
	}
	else
	{
		if (conf->fzero)
			size++;
		ft_printbuff(conf, size);
		conf->fzero = 0;
	}
}
