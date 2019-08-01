/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:46:51 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/31 13:25:11 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			write_binary(t_asm *glob, int op_index, char *byte, int type)
{
	if ((op_index < 8 || op_index == 12) && (type & T_DIR))
	{
		*(glob->ptr++) = *(byte + 3);
		*(glob->ptr++) = *(byte + 2);
	}
	*(glob->ptr++) = *(byte + 1);
	*(glob->ptr++) = *byte;
}

static int		check_invalid_label(t_input *input, char **param_tab)
{
	if (ft_strchr(param_tab[0], ':'))
	{
		ft_freetab(param_tab);
		return (print_error(INVALID_LABEL, input->line_number));
	}
	ft_freetab(param_tab);
	return (print_error(INVALID_INSTRUCTION, input->line_number));
}

static int		param_error(char **tab, int line_nbr)
{
	ft_freetab(tab);
	return (print_error(INVALID_PARAMS, line_nbr));
}

int				check_instruction(t_asm *glob, char **tab, t_input *input)
{
	char			**param_tab;

	input->byte_nbr = glob->byte_nbr;
	if (tab[0] && (tab[0][0] == '#' || tab[0][0] == ';'))
		return (1);
	if (!(param_tab = custom_split(tab)))
		return (0);
	if ((input->op_index = is_instruction(param_tab[0])) == -1)
		return (check_invalid_label(input, param_tab));
	glob->byte_nbr++;
	if (!(input->bin = ft_strnew(11)))
		return (ret_freetab(param_tab, 0));
	glob->ptr = input->bin;
	*(glob->ptr++) = (g_op_tab[input->op_index].id);
	glob->ocp_ptr = glob->ptr;
	if (g_op_tab[input->op_index].ocp)
		glob->ptr++;
	if (!param_tab[1]
	|| !check_params(glob, param_tab + 1, g_op_tab[input->op_index], input))
		return (param_error(param_tab, input->line_number));
	input->bin_size = glob->byte_nbr - input->byte_nbr;
	glob->inst_count += input->bin_size;
	return (ret_freetab(param_tab, 1));
}
