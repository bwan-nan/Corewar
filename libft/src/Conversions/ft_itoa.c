/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:15:58 by bwan-nan          #+#    #+#             */
/*   Updated: 2018/11/20 13:28:10 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	get_str_len(int n)
{
	size_t		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char		*str;
	size_t		str_len;
	int			sign;

	sign = 1;
	str_len = get_str_len(n);
	if (n < 0)
	{
		sign = -1;
		str_len++;
	}
	if (!(str = ft_strnew(str_len)))
		return (NULL);
	str[--str_len] = n % 10 * sign + 48;
	while (n /= 10)
		str[--str_len] = n % 10 * sign + 48;
	if (sign == -1)
		str[0] = '-';
	return (str);
}
