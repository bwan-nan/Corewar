/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:06:22 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 17:06:24 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_trim(char *str)
{
	char	*new_string;
	int		start;
	int		end;

	start = 0;
	while (str[start] && ft_iswhitespace(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (ft_iswhitespace(str[end]))
		end--;
	if (!(new_string = ft_strsub(str, start, end - start + 1)))
		return (NULL);
	ft_strdel(&str);
	return (new_string);
}
