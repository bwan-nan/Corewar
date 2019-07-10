/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:40:48 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 15:31:44 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	round_float(char *number, int ret)
{
	int	len;
	int	i;

	len = ft_strlen(number);
	i = len;
	while (i--)
	{
		if (number[i] - 48 + ret > 9 && number[i] != '.')
		{
			number[i] = '0';
			ret = 1;
		}
		else if (number[i] != '.')
		{
			number[i] = number[i] + ret;
			ret = 0;
		}
	}
}

int		format_float(t_conv *conv, char *number)
{
	int		len;
	char	*tmp;
	int		ret;
	int		i;

	ret = 0;
	len = ft_strchr_index(number, '.') + (!PREC ? 0 : 1) + PREC;
	if ((number[len] == '.' && number[len + 1] - 48 >= 5)
	|| (number[len] != '.' && number[len] - 48 >= 5))
		ret = 1;
	if (!(RESULT = ft_strsub(number, 0, len)))
		return (-1);
	if (ret)
		round_float(RESULT, ret);
	i = *(ft_str_notchr(RESULT, '0')) == '.' ? 1 : 0;
	if (ft_strlen(RESULT) > 1)
	{
		tmp = RESULT;
		RESULT = ft_strdup(ft_str_notchr(RESULT, '0') - i);
		if (!RESULT)
			return (-1);
		ft_strdel(&tmp);
	}
	return (0);
}

void	str_mult_by_two(char **str, t_conv *conv)
{
	int			j;
	int			ret;

	ret = 0;
	j = INDEX;
	while (j > INDEX - LEN)
	{
		if (str[0][j] < '5' && str[0][j] >= '0')
		{
			str[0][j] = str[0][j] + str[0][j] - 48 + ret;
			ret = 0;
		}
		else if (str[0][j] <= '9' && str[0][j] >= '5')
		{
			str[0][j] = ((str[0][j] - 48) * 2) % 10 + 48 + ret;
			ret = 1;
			if (j == INDEX - LEN + 1)
				LEN++;
		}
		if (str[0][j] == '.')
			LEN += 1;
		j--;
	}
}

void	str_div_by_two(char **str, t_conv *conv)
{
	int	i;
	int	tmp;
	int	ret;

	ret = 0;
	i = INDEX;
	while (i < INDEX + LEN && str[0][i])
	{
		if (str[0][i] == '.')
			LEN++;
		else
		{
			tmp = (str[0][i] - 48) % 2;
			str[0][i] = ((str[0][i] - 48) / 2 + ret) + 48;
			ret = tmp == 0 ? 0 : 5;
			if (ret && i == INDEX + LEN - 1)
				LEN++;
		}
		i++;
	}
}

void	str_addition(char **result, char *add)
{
	int i;
	int len;
	int j;
	int	ret;

	i = 0;
	ret = 0;
	len = ft_strlen(*result);
	while (i < len)
	{
		j = len - 1 - i;
		if (result[0][j] == '.')
			result[0][j] = '.';
		else if (result[0][j] + add[j] - 48 + ret <= '9')
		{
			result[0][j] += add[j] - 48 + ret;
			ret = 0;
		}
		else if (result[0][j] + add[j] - 48 + ret > '9')
		{
			result[0][j] = (result[0][j] - 48 + add[j] - 48 + ret) % 10 + 48;
			ret = 1;
		}
		i++;
	}
}
