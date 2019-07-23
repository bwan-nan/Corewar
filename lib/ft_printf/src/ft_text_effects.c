/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_text_effects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 00:50:01 by fdagbert          #+#    #+#             */
/*   Updated: 2018/09/03 19:54:53 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_effects		g_effects[] = {
	{"{OFF}", "\033[0m", 4},
	{"{BOLD}", "\033[1m", 4},
	{"{LIGHT}", "\033[2m", 4},
	{"{ITAL}", "\033[3m", 4},
	{"{UNDER}", "\033[4m", 4},
	{"{BLINK}", "\033[5m", 4},
	{"{INVER}", "\033[7m", 4},
	{"{HIDE}", "\033[8m", 4},
	{"{STRIK}", "\033[9m", 4},
	{"{BLA}", "\033[30m", 5},
	{"{RED}", "\033[31m", 5},
	{"{GRE}", "\033[32m", 5},
	{"{YEL}", "\033[33m", 5},
	{"{BLU}", "\033[34m", 5},
	{"{MAG}", "\033[35m", 5},
	{"{CYA}", "\033[36m", 5},
	{"{WHI}", "\033[37m", 5},
	{"{BKBLA}", "\033[40m", 5},
	{"{BKRED}", "\033[41m", 5},
	{"{BKGRE}", "\033[42m", 5},
	{"{BKYEL}", "\033[43m", 5},
	{"{BKBLU}", "\033[44m", 5},
	{"{BKMAG}", "\033[45m", 5},
	{"{BKCYA}", "\033[46m", 5},
	{"{BKWHI}", "\033[47m", 5},
	{NULL, NULL, 0}
};

int			ft_text_effects(t_config *conf, const char *str)
{
	int		i;
	int		j;

	i = 0;
	while (g_effects[i].keys)
	{
		j = 0;
		while (str[j] == g_effects[i].keys[j])
		{
			j++;
			if (g_effects[i].keys[j] == '\0')
			{
				ft_addbuff(conf, 0);
				write(1, g_effects[i].code, g_effects[i].len);
				return (j);
			}
		}
		i++;
	}
	return (0);
}
