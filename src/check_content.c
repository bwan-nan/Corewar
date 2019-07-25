/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:44:17 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 13:44:19 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*get_first_word(char *str, int *len)
{
	char	*start;
	int		i;

	//ft_putendl("in get_first_word");
	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	start = &str[i];
	//ft_putendl("start:");
	//ft_putendl(start);
	while (str[i] && ft_strchr(LABEL_CHARS, str[i++]))
		(*len)++;
	//ft_putendl("out of get_first_word");
	//ft_putnbrendl(*len);
	return (start);
}

int				check_content(t_asm *glob, t_input *input, char *line)
{
	char		**tab;
	char		*first_word;
	int			len;
	t_label		*label;

	//ft_putendl("line:");
	//ft_putendl(line);
	len = 0;
	tab = NULL;
	label = NULL;
	if (glob->current_label)
		label = glob->current_label->content;
	first_word = get_first_word(line, &len);
	if (first_word && first_word[len] == ':')
	{
		if (label && !ft_strnequ(first_word, label->name, len))
		{
		/*	ft_putendl(line);
			ft_putendl(first_word);
			ft_putendl(label->name);*/
			return (print_error(INVALID_LABEL, input->line_number));
		}
		if (first_word[len + 1]
		&& !(tab = ft_split_whitespaces(&first_word[len + 1])))
			return (print_error(MALLOC_ERROR, 0));
		if (glob->current_label)
		{
			label = glob->current_label->content;
			label->byte_nbr = glob->byte_nbr;
		}
		glob->current_label = glob->current_label->next;
	}
	else
	{
		//ft_putendl("no label line");
		if (!(tab = ft_split_whitespaces(line)))
			return (print_error(MALLOC_ERROR, 0));
	}
	if (tab && tab[0])
	{
		if (!check_instruction(glob, tab, input))
		{
			//ft_putendl("check content");
			return (print_error(INVALID_INSTRUCTION, input->line_number));
		}
	}
	//freetab...
	return (1);
}
