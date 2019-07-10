/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:45:49 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/22 18:44:56 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_string_len(va_list list, const char *format)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1] == 's')
		{
			if (!(str = va_arg(list, char *)))
				return (0);
			len += ft_strlen(str);
			i++;
		}
		else
			len++;
	}
	return (len);
}

static int		copy_args(va_list list, const char *format, char *result)
{
	int			len;
	int			i;
	char		*str;

	i = -1;
	len = 0;
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1] == 's')
		{
			if (!(str = va_arg(list, char *)))
				return (0);
			ft_strcpy(result + len, str);
			len += ft_strlen(str);
			i++;
		}
		else
		{
			result[len] = format[i];
			len++;
		}
	}
	return (1);
}

int				variadic_strjoin(char **ret, const char *format, ...)
{
	va_list		args;
	va_list		args2;
	int			len;
	char		*tmp;

	tmp = NULL;
	va_start(args, format);
	ft_memcpy((void *)args2, (void *)args, sizeof(args));
	len = get_string_len(args, format);
	tmp = *ret;
	if (!(*ret = ft_strnew(len + ft_strlen(tmp))))
		return (0);
	if (tmp)
		ft_strcpy(*ret, tmp);
	if (!copy_args(args2, format, *ret + ft_strlen(tmp)))
		return (0);
	if (tmp)
		ft_strdel(&tmp);
	va_end(args);
	return (1);
}
