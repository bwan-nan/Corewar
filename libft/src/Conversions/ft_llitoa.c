/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:15:18 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 22:54:31 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_str_len(long long n)
{
	int		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_llitoa(long long nb)
{
	char				*str;
	int					sign;
	int					str_len;

	sign = 1;
	str_len = get_str_len(nb);
	if (nb < 0)
	{
		sign = -1;
		str_len++;
	}
	if (!(str = ft_strnew(str_len)))
		return (NULL);
	str[--str_len] = nb % 10 * sign + 48;
	while (nb /= 10)
		str[--str_len] = nb % 10 * sign + 48;
	if (sign == -1)
		str[0] = '-';
	return (str);
}
