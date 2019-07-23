/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:04:18 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/23 01:15:30 by fdagbert         ###   ########.fr       */
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
	char		error_tab[20][45];

	ft_bzero(error_tab[0], 45);
	ft_strcpy(error_tab[1], "Memory limit (malloc)");
	ft_strcpy(error_tab[2], "Can not open champion file (wrong path)");
	ft_strcpy(error_tab[3], "Can not read champion file (GNL)");
	ft_strcpy(error_tab[4], "Wrong binary file format (.cor)");
	ft_strcpy(error_tab[5], "No one champion to fight");
	ft_strcpy(error_tab[6], "Too much champions to fight");
	ft_strcpy(error_tab[7], "32 bits system detected. Set REG_SIZE to 4");
	ft_strcpy(error_tab[8], "64 bits system detected. Set REG_SIZE to 8");
	ft_strcpy(error_tab[9], "Architecture system unknow. Check sizeof(int)");
	ft_strcpy(error_tab[10], "Champion binary file corrupted");
	ft_strcpy(error_tab[11], "Champion binary file too big");
	ft_strcpy(error_tab[12], "Champion size too big (instructions)");
	ft_strcpy(error_tab[13], "Champion without instruction");
	ft_strcpy(error_tab[14], "Wrong magic number");
	ft_strcpy(error_tab[15], "Wrong padding");
	ft_strcpy(error_tab[16], "Wrong op_code byte in champion instruction");
	ft_strcpy(error_tab[17], "Wrong ocp byte in champion instruction");
	ft_strcpy(error_tab[18], "#No one ant in the hex !");
	ft_strcpy(error_tab[19], "#Ant number out of range (int)");
	ft_print_error(error_tab[error], conf);
}

static void		ft_init_error_opt(int error, t_conf *conf)
{
	char		error_opt[5][45];

	ft_strcpy(error_opt[0], "Invalid option: see help (-h)");
	ft_strcpy(error_opt[1], "Option already enabled");
	ft_strcpy(error_opt[2], "Can not open/close file man_lem");
	ft_strcpy(error_opt[3], "Dump option must be a positive number");
	ft_bzero(error_opt[4], 45);
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
