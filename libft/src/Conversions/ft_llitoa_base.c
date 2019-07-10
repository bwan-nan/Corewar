/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:54:36 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 22:54:31 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int		get_str_len(long long n, int base)
{
	int		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char			*ft_llitoa_base(long long nb, int base)
{
	char				*str;
	char				base_string[17];
	int					len;
	unsigned long long	tmp;

	ft_strcpy(base_string, "0123456789abcdef");
	if (base < 2 || base > 16)
		return (0);
	if (base == 10)
		return (ft_llitoa(nb));
	tmp = nb < 0 ? ULLONG_MAX + nb + 1 : nb;
	len = get_str_len(tmp, base);
	if (!(str = ft_strnew(len)))
		return (0);
	str[--len] = base_string[tmp % base];
	while (tmp /= base)
		str[--len] = base_string[tmp % base];
	return (str);
}
