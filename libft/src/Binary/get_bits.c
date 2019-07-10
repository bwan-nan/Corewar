/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:31:38 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 22:55:03 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_bits(void *octet, int size)
{
	int				i;
	int				j;
	char			*ptr;
	char			*str;

	if (!(str = (char *)malloc(sizeof(*str) * (size * 8 + 1))))
		return (NULL);
	j = size;
	ptr = (char *)octet;
	while (j--)
	{
		i = 8;
		while (i--)
			str[j * 8 + 8 - (i + 1)] = (*ptr >> i & 1) + '0';
		ptr++;
	}
	str[size * 8] = '\0';
	return (str);
}
