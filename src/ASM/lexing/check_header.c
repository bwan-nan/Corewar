/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:46:46 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/29 17:53:24 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** status == 0 ? on accepte les .name et .comment
** status == 1 ? on accepte .comment et pas .name
** status == 2 ? on accepte .name et pas .comment
** status == 3 ? on doit completer .name (apres status 0)
** status == 4 ? on doit completer .comment (apres status 0)
** status == 5 ? on doit completer .name
** status == 6 ? on doit completer .comment
** status == 7 ? fini
** 0->(4)->2->(5)->7
** 0->(3)->1->(6)->7
*/

static int		complete_header(t_input *input, int *status)
{
	int		quote;

	if ((quote = ft_strnchr_index(input->line, 1, '"')) != -1)
	{
		if (!(input->bin = ft_strsub(input->line, 0, quote)))
			return (0);
		input->bin_size = ft_strlen(input->bin);
		if (!check_after_quote(input->line, quote))
			return (print_error(LEXICAL_ERROR, input->line_number));
		update_status(&input->type, status);
		return (1);
	}
	if (!(input->bin = ft_strdup(input->line)))
		return (0);
	input->bin_size = ft_strlen(input->bin);
	if (*status == 3 || *status == 5)
		input->type = 'n';
	else if (*status == 4 || *status == 6)
		input->type = 'c';
	return (1);
}

int				update_prog_lengths(t_asm *glob, t_input *input)
{
	if (ft_strchr("cC", input->type))
		glob->comment_length += input->bin_size;
	else if (ft_strchr("nN", input->type))
		glob->name_length += input->bin_size;
	if (glob->name_length > 128)
		return (print_error(NAME_ERROR, 0));
	else if (glob->comment_length > 2048)
		return (print_error(COMMENT_ERROR, 0));
	return (1);
}

static int		get_header(t_input *input, int *status)
{
	int	first;
	int	second;

	if ((first = ft_strnchr_index(input->line, 1, '"')) == -1)
		return (header_status(*status));
	if (!check_before_quote(input, input->line, first, status))
		return (print_error(LEXICAL_ERROR, input->line_number));
	if ((second = ft_strnchr_index(input->line, 2, '"')) != -1)
	{
		if (!check_after_quote(input->line, second))
			return (print_error(LEXICAL_ERROR, input->line_number));
	}
	else
		second = ft_strlen(input->line);
	if (!(input->bin = ft_strsub(input->line, first + 1, second - first - 1)))
		return (0);
	input->bin_size = ft_strlen(input->bin);
	return (1);
}

static int		check_validity(t_input *input, int *status)
{
	if (*status < 3)
	{
		if (!get_header(input, status))
			return (0);
	}
	else if (!complete_header(input, status))
		return (0);
	return (1);
}

int				check_header(t_asm *glob, t_list **input)
{
	int			status;
	t_input		*content;

	status = 0;
	while (*input)
	{
		content = (*input)->content;
		if (status < 3
		&& (is_empty(content->line) || is_comment(content->line)))
		{
			*input = (*input)->next;
			continue ;
		}
		if (!check_validity(content, &status))
			return (0);
		if (status >= 3 && status <= 6 && (++content->bin_size))
			if (!(content->bin = ft_strjoinf(content->bin, "\n")))
				return (0);
		if (!update_prog_lengths(glob, content))
			return (0);
		if (status == 7)
			break ;
		*input = (*input)->next;
	}
	return (header_status(status));
}
