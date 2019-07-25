/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:47:05 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 17:09:27 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			is_empty(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!ft_iswhitespace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int			is_comment(char *line)
{
	int		i;

	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	return (line[i] && (line[i] == '#' || line[i] == ';'));
}

int			lexing(t_asm *glob)
{
	t_list	*input;
	char	*line;
	int		valid_header;

	valid_header = 0;
	input = glob->input;
	while (input)
	{
		line = ((t_input *)input->content)->line;
		if (!is_empty(line) && !is_comment(line))
		{
			if (!valid_header)
			{
				if (!(valid_header = check_header(glob, &input)))
					return (0);
				if (!update_labels(glob, input->next, &glob->labels))
					return (print_error(MALLOC_ERROR, 0));
			}
			else if (!check_content(glob, input->content, line))
				return (0);
		}
		input = input->next;
	}
	fill_queue(glob);
	return (1);
}
