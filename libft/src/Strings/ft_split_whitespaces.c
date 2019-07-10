/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 13:35:31 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 22:52:48 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		count_words(char *str)
{
	int i;
	int num_words;
	int len;

	i = 0;
	num_words = 0;
	len = 0;
	while (str[i])
	{
		if (ft_iswhitespace(str[i]))
			len = 0;
		else if (++len == 1)
			num_words++;
		i++;
	}
	return (num_words);
}

char			**ft_split_whitespaces(char *str)
{
	char	**tab;
	int		i;
	int		len;
	int		word_index;

	word_index = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (count_words(str) + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		len = 0;
		while (!(ft_iswhitespace(str[i + len])) && str[i + len])
			len++;
		if (len)
		{
			tab[word_index] = ft_strsub(str, i, len);
			word_index++;
			i += len - 1;
		}
		i++;
	}
	tab[word_index] = 0;
	return (tab);
}
