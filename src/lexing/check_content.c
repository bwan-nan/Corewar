/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:44:17 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/29 18:51:19 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*get_first_word(char *str, int *len)
{
	char	*start;
	int		i;

	i = 0;
	*len = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	start = &str[i];
	while (str[i] && ft_strchr(LABEL_CHARS, str[i++]))
		(*len)++;
	return (start);
}

static int		look_for_instruction(t_asm *glob, t_input *input, char **tab)
{
	if (tab && tab[0])
	{
		if (!check_instruction(glob, tab, input))
		{
			ft_freetab(tab);
			return (print_error(INVALID_INSTRUCTION, input->line_number));
		}
	}
	ft_freetab(tab);
	return (2);
}

int				check_content(t_asm *glob, t_input *input, char *line)
{
	char		**tab;
	char		*first_word;
	int			len;
	t_label		*label;

	tab = NULL;
	label = NULL;
	if (glob->current_label)
		label = glob->current_label->content;
	if (!(first_word = get_first_word(line, &len)))
		return (print_error(INVALID_LABEL, input->line_number));
	if (first_word && first_word[len] == ':')
	{
		if (label && !ft_strnequ(first_word, label->name, len))
			return (print_error(INVALID_LABEL, input->line_number));
		if (first_word[len + 1]
		&& !(tab = ft_split_whitespaces(&first_word[len + 1])))
			return (print_error(MALLOC_ERROR, 0));
		if (glob->current_label && (label = glob->current_label->content))
			label->byte_nbr = glob->byte_nbr;
		glob->current_label = glob->current_label->next;
	}
	else if (!(tab = ft_split_whitespaces(line)))
		return (print_error(MALLOC_ERROR, 0));
	return (look_for_instruction(glob, input, tab));
}
