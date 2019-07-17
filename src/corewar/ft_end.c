/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:04:18 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/17 17:42:50 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_print_error(char *error, t_conf *conf)
{
	if (conf->opt[5])
		ft_printf("%@{RED}ERROR\n%@%s{OFF}\n", 1, 2, error);
	else
		ft_printf("%@ERROR\n%@%s\n", 1, 2, error);
}

static void		ft_init_error_cor(int error, t_conf *conf)
{
	char		error_tab[20][35];

	ft_bzero(error_tab[0], 35);
	ft_strcpy(error_tab[1], "Memory limit (malloc)");
	ft_strcpy(error_tab[2], "Can not read map file (GNL)");
	ft_strcpy(error_tab[3], "#Memory limit (malloc)");
	ft_strcpy(error_tab[4], "#Missing map data");
	ft_strcpy(error_tab[5], "#Missing start/end");
	ft_strcpy(error_tab[6], "#Wrong ants format");
	ft_strcpy(error_tab[7], "#Wrong comment format");
	ft_strcpy(error_tab[8], "#Wrong command format");
	ft_strcpy(error_tab[9], "#Wrong room name");
	ft_strcpy(error_tab[10], "#Wrong edge name");
	ft_strcpy(error_tab[11], "#Wrong room format");
	ft_strcpy(error_tab[12], "#Wrong coord format");
	ft_strcpy(error_tab[13], "#Room already exist");
	ft_strcpy(error_tab[14], "#Room connected to itself");
	ft_strcpy(error_tab[15], "#Room already connected");
	ft_strcpy(error_tab[16], "#Room name out of range [30]");
	ft_strcpy(error_tab[17], "#Room coord out of range (int)");
	ft_strcpy(error_tab[18], "#No one ant in the hex !");
	ft_strcpy(error_tab[19], "#Ant number out of range (int)");
	ft_print_error(error_tab[error], conf);
}

static void		ft_init_error_opt(int error, t_conf *conf)
{
	char		error_opt[5][35];

	ft_strcpy(error_opt[0], "Invalid option: see help (-h)");
	ft_strcpy(error_opt[1], "Option already enabled");
	ft_strcpy(error_opt[2], "Can not open/close file man_lem");
	ft_strcpy(error_opt[3], "#Can not open/close file lem.dot");
	ft_bzero(error_opt[4], 35);
	ft_print_error(error_opt[error], conf);
}

int				ft_end(int error, t_conf *conf)
{
	if (error < 0)
	{
		if (error > -20)
			ft_init_error_cor(-(error), conf);
		else
			ft_init_error_opt(-(error + 20), conf);
	}
	ft_clean(conf);
	return (error);
}
