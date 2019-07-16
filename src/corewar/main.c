/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:35:44 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/16 18:23:18 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


static void			ft_init_conf(int i, t_conf *conf)
{
	while (i < D_OPT_MAX)
		conf->opt[i++] = 0;
	i = 0;
	while (i < MEM_SIZE)
		conf->grid[i++] = 0;
	conf->op_tab = NULL;
}

int		main(void)
{
	t_conf		conf;
	
	ft_init_conf(0, &conf);
	ft_init_op(&conf);
	return (0);
}
