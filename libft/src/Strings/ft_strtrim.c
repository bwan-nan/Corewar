/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 12:20:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 22:52:48 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (0);
	i = 0;
	j = ft_strlen(s);
	while (ft_iswhitespace(s[i]))
		i++;
	while (i != j && (ft_iswhitespace(s[j - 1])))
		j--;
	if (!(str = (char *)malloc(sizeof(char) * (j - i + 1))))
		return (0);
	str[j - i] = '\0';
	ft_strncpy(str, s + i, j - i);
	return (str);
}
