/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:06:13 by fdagbert          #+#    #+#             */
/*   Updated: 2017/11/23 19:47:00 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char *ptr;

	ptr = dest;
	while (*src != '\0')
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
