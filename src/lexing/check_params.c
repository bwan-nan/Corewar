/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:05:52 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/29 16:42:13 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_register(t_asm *glob, t_input *input, char *str)
{
	if (ft_strlen(str) > 3 || !str[1] || !ft_isdigits(&str[1]))
		return (0);
	update_ocp(glob, input, T_REG);
	*(glob->ptr++) = ft_atoi(str + 1);
	glob->byte_nbr++;
	return (1);
}

int		check_direct(t_asm *glob, t_input *input, char *str)
{
	t_label		*label;
	int			address;

	if (str[1] == ':')
	{
		if (!str[2] || !(label = is_label(&str[2], glob->labels)))
			return (0);
		add_to_queue(glob, input, label, T_DIR);
	}
	else if (str[1] && ft_isnumber(&str[1]))
	{
		address = ft_atoi(&str[1]);
		write_binary(glob, input->op_index, (char *)(&address), T_DIR);
	}
	else
		return (0);
	update_ocp(glob, input, T_DIR);
	glob->byte_nbr += (input->op_index < 8 || input->op_index == 12) ? 4 : 2;
	return (1);
}

int		check_indirect(t_asm *glob, t_input *input, char *str)
{
	t_label		*label;
	int			address;
	int			ret;

	if (str[0] == ':')
	{
		if (!(label = is_label(&str[1], glob->labels)))
			return (0);
		add_to_queue(glob, input, label, T_IND);
	}
	else if (str[0] && (ret = ft_isnumber(str)))
	{
		address = ft_atoi(str);
		write_binary(glob, input->op_index, (char *)(&address), T_IND);
	}
	else
		return (0);
	update_ocp(glob, input, T_IND);
	glob->byte_nbr += 2;
	return (1);
}

int		check_param(t_asm *glob, char *str, char type, t_input *input)
{
	if (*str == 'r' && (type & T_REG))
		return (check_register(glob, input, str));
	else if (*str == '%' && (type & T_DIR))
		return (check_direct(glob, input, str));
	else if (type & T_IND)
		return (check_indirect(glob, input, str));
	else
		return (0);
	return (1);
}

int		check_params(t_asm *glob, char **tab, t_op op, t_input *input)
{
	int		j;

	if (get_tab_len(tab) != op.nb_params * 2 - 1)
		return (0);
	glob->param = 0;
	glob->byte_nbr += g_op_tab[input->op_index].ocp;
	j = 0;
	while (j < op.nb_params * 2 - 1)
	{
		if (j % 2)
		{
			if (!ft_strequ(tab[j], ","))
				return (0);
		}
		else if (!check_param(glob, tab[j]
		, op.params_type[(glob->param)++], input))
			return (0);
		j++;
	}
	return (1);
}
