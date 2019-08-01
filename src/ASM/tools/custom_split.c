/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:46:56 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/31 12:54:56 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		update_count(char c, int *count, int *len)
{
	if (c == ',' || c == '%')
	{
		*len = 0;
		*count += (c == '%' && *len) || c == ',' ? 1 : 0;
	}
	else if (c == '#' || c == ';')
		return (1);
	else if (++(*len) == 1)
		(*count)++;
	return (0);
}

static int		count_params(char **tab)
{
	int		i;
	int		j;
	int		count;
	int		len;

	count = 0;
	len = 0;
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (update_count(tab[i][j], &count, &len))
				return (count);
			j++;
		}
		i++;
		len = 0;
	}
	return (count);
}

static int		update_tab(char **param, char *str, int *i, int len)
{
	if (len == 0 && str[*i] == ',')
	{
		if (!(*param = ft_strdup(",")))
			return (0);
	}
	else
	{
		if (!(*param = ft_strsub(str, *i, len)))
			return (0);
		*i += len - 1;
	}
	return (1);
}

static int		add_word(char **tab, char **param_tab
				, int *word_index, int params_count)
{
	char	*str;
	int		i;
	int		len;

	str = *tab;
	i = 0;
	while (str && str[i])
	{
		len = 0;
		while (str[i + len] && ((!ft_strchr(",;#%", str[i + len]) && len != 0)
		|| (!ft_strchr(",;#", str[i + len]) && len == 0)))
			len++;
		if (!update_tab(&param_tab[(*word_index)++], str, &i, len))
			return (0);
		if (*word_index == params_count)
			return (1);
		i++;
	}
	if (tab && tab[0] && tab[1])
		return (add_word(tab + 1, param_tab, word_index, params_count));
	return (1);
}

char			**custom_split(char **tab)
{
	int		len;
	char	**param_tab;
	int		word_index;

	len = count_params(tab);
	word_index = 0;
	param_tab = NULL;
	if (!(param_tab = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	param_tab[len] = 0;
	if (!add_word(tab, param_tab, &word_index, len))
	{
		ft_freetab(param_tab);
		return (NULL);
	}
	return (param_tab);
}
