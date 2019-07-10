/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:08:39 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 22:54:31 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ullitoa(unsigned long long nb)
{
	int					len;
	unsigned long long	nbr;
	char				*str;

	nbr = nb;
	len = 1;
	while (nbr /= 10)
		len++;
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (0);
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
