/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 21:26:25 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/17 17:52:53 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		ft_printbase(int nb)
{
	if (nb < 10)
		nb += '0';
	else
		nb += ('A' - 10);
	return (nb);
}

static void		ft_fillstr(int nbr, int size, char *str, int base)
{
	if (nbr == 0)
		str[0] = '0';
	else if (nbr < 0)
	{
		nbr *= (-1);
		if (base == 10)
			str[0] = '-';
		else
			size--;
	}
	str[size--] = '\0';
	while (nbr > 0)
	{
		str[size] = nbr % base;
		str[size] = ft_printbase(str[size]);
		nbr /= base;
		size--;
	}
}

static char		*ft_printoverflow(int base)
{
	char	*ovftab;
	int		len;

	ovftab = ft_itoa_base(-2147483647, base);
	len = ft_strlen(ovftab) - 1;
	if (ovftab[len] + 1 < ft_printbase(base))
		ovftab[len]++;
	else
	{
		while (len >= 0 && ((ovftab[len] + 1) == ft_printbase(base)))
			ovftab[len--] = '0';
		if (len < 0)
		{
			ovftab[0] = '1';
			ovftab[31] = '0';
		}
		else
			ovftab[0]++;
	}
	return (ovftab);
}

char			*ft_itoa_base(int n, int base)
{
	int		size;
	int		temp;
	char	*str;

	size = 0;
	temp = n;
	str = NULL;
	if (n != -2147483648)
	{
		if (n <= 0)
		{
			size++;
			temp *= (-1);
		}
		while (temp > 0)
		{
			size++;
			temp /= base;
		}
		if (!(str = ft_strnew(size)))
			return (NULL);
		ft_fillstr(n, size, str, base);
		return (str);
	}
	return (ft_printoverflow(base));
}
