/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:46:07 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/29 15:11:21 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_after_quote(char *line, int n)
{
	char	**tab;

	if (line[n + 1])
	{
		if (!(tab = ft_split_whitespaces(line + n + 1)))
			return (0);
		if (tab[0] && !(tab[0][0] == '#' || tab[0][0] == ';'))
		{
			ft_freetab(tab);
			return (0);
		}
		ft_freetab(tab);
	}
	return (1);
}

int		check_before_quote(t_input *input, char *line, int n, int *status)
{
	char		*str;

	if (!(str = ft_trim(ft_strsub(line, 0, n))))
		return (0);
	if (ft_strequ(str, ".name") && *status != 1)
	{
		if (ft_strnchr_index(line, 2, '"') != -1 && (input->type = 'N'))
			*status = *status == 0 ? 1 : 7;
		else if ((input->type = 'n'))
			*status = *status == 0 ? 3 : 5;
	}
	else if (ft_strequ(str, ".comment") && *status != 2)
	{
		if (ft_strnchr_index(line, 2, '"') != -1 && (input->type = 'C'))
			*status = *status == 0 ? 2 : 7;
		else if ((input->type = 'c'))
			*status = *status == 0 ? 4 : 6;
	}
	else
	{
		ft_strdel(&str);
		return (0);
	}
	ft_strdel(&str);
	return (1);
}
