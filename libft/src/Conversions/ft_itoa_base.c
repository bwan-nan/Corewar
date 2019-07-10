/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 21:01:43 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/08 17:42:28 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		get_str_len(int n, int base)
{
	int		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char			*ft_itoa_base(int value, int base)
{
	int		str_len;
	char	*str;
	int		sign;
	char	base_string[17];

	sign = 1;
	ft_strcpy(base_string, "0123456789ABCDEF");
	if (value == 0 || base < 2 || base > 16)
		return ("0");
	str_len = get_str_len(value, base);
	if (value < 0 && base == 10)
	{
		str_len++;
		sign = -1;
	}
	if (!(str = ft_strnew(str_len)))
		return (NULL);
	str[--str_len] = base_string[value % base * sign];
	while (value /= base)
		str[--str_len] = base_string[value % base * sign];
	if (sign == -1 && base == 10)
		str[0] = '-';
	return (str);
}
