/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 08:07:31 by fdagbert          #+#    #+#             */
/*   Updated: 2017/11/28 08:39:17 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupcase(char *str)
{
	char *ptr;

	ptr = str;
	while (*ptr != '\0')
	{
		*ptr = ft_toupper(*ptr);
		ptr++;
	}
	return (str);
}
