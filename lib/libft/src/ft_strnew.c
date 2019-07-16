/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 19:43:01 by fdagbert          #+#    #+#             */
/*   Updated: 2019/04/11 15:36:58 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *ptr;

	if (!(ptr = (char *)malloc(sizeof(*ptr) * size + 1)))
		return (NULL);
	else
	{
		ft_bzero(ptr, size + 1);
		return (ptr);
	}
}
