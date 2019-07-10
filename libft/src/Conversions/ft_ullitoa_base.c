/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:46:15 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 22:54:31 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	get_str_len(unsigned long long n, int base)
{
	int		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char		*ft_ullitoa_base(unsigned long long nb, int base)
{
	char				*str;
	char				base_string[17];
	int					len;

	ft_strcpy(base_string, "0123456789abcdef");
	if (base < 2 || base > 16)
		return (0);
	if (base == 10)
		return (ft_llitoa(nb));
	len = get_str_len(nb, base);
	if (!(str = ft_strnew(len)))
		return (0);
	str[--len] = base_string[nb % base];
	while (nb /= base)
		str[--len] = base_string[nb % base];
	return (str);
}
