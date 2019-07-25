/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:03:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 15:09:05 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	update_ocp(t_asm *glob, t_input *input, char type)
{
	if (g_op_tab[input->op_index].ocp)
	{
		if (type & T_REG)
			*(glob->ocp_ptr) |= REG_CODE << (8 - 2 * glob->param);
		else if (type & T_DIR)
			*(glob->ocp_ptr) |= DIR_CODE << (8 - 2 * glob->param);
		else if (type & T_IND)
			*(glob->ocp_ptr) |= IND_CODE << (8 - 2 * glob->param);
	}
}

int		is_instruction(char *str)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		if (ft_strequ(g_op_tab[i].name, str))
			return (i);
		i++;
	}
	return (-1);
}

int		ft_isnumber(char *str)
{
	int						i;
	char					cpy[21];
	unsigned long long		nb;
	static int				call = 0;

	if (!str || (*str == '-' && call > 0))
		return (0);
	else if (*str == '-' && call++ == 0)
		return (ft_isnumber(str + 1));
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	if (i > 20)
		return (0);
	if (i == 20)
	{
		ft_strcpy(cpy, str);
		if ((nb = ft_atoull(cpy)) > 1844674407370955161)
			return (0);
		else if (nb == 1844674407370955161 && str[19] > '5')
			return (0);
	}
	return (!(call = 0));
}

int		ft_isdigits(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

t_label	*is_label(char *str, t_list *label)
{
	while (label)
	{
		if (ft_strequ(str, ((t_label *)label->content)->name))
			return (label->content);
		label = label->next;
	}
	return (NULL);
}
