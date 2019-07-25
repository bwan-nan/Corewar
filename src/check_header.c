#include "asm.h"

static int		check_after_quote(char *line, int n)
{
	char	**tab;

	if (line[n + 1])
	{
		if (!(tab = ft_split_whitespaces(line + n + 1)))
			return (0);
		if (tab[0] && !(tab[0][0] == '#' || tab[0][0] == ';'))
		{
			ft_freetab(tab);
			return (0);
		}
		ft_freetab(tab);
	}
	return (1);
}

static void		update_status(char *type, int *status)
{
	if (*status == 3)
	{
		*type = 'N';
		*status = 1;
	}
	else if (*status == 4)
	{
		*type = 'C';
		*status = 2;
	}
	else if (*status == 5 || *status == 6)
	{
		*type = *status == 5 ? 'N' : 'C';
		*status = 7;
	}
}

static int		complete_header(t_input *input, int *status)
{
	int		quote;

	if ((quote = ft_strnchr_index(input->line, 1, '"')) != -1)
	{
		if (!(input->bin = ft_strsub(input->line, 0, quote)))
			return (0);
		input->bin_size = ft_strlen(input->bin);
		update_status(&input->type, status);
		return (check_after_quote(input->line, quote));
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

static int		check_before_quote(t_input *input, char *line, int n, int *status)
{
	char		*str;

	if (!(str = ft_trim(ft_strsub(line, 0, n))))
		return (0);
	if (ft_strequ(str, ".name") && *status != 1)
	{
		if (ft_strnchr_index(line, 2, '"') != -1 && (input->type = 'N'))
			*status = *status == 0 ? 1 : 7;
		else if ((input->type = 'n'))
			*status = *status == 0 ? 3 : 5;
	}
	else if (ft_strequ(str, ".comment") && *status != 2)
	{
		if (ft_strnchr_index(line, 2, '"') != -1 && (input->type = 'C'))
			*status = *status == 0 ? 2 : 7;
		else if ((input->type = 'c'))
			*status = *status == 0 ? 4 : 6;
	}
	else
	{
		ft_strdel(&str);
		return (0);
	}
	ft_strdel(&str);
	return (1);
}

//print_error specifique au header (en fonction du status)
// status == 0 ? on accepte les .name et .comment
// status == 1 ? on accepte .comment et pas .name
// status == 2 ? on accepte .name et pas .comment
// status == 3 ? on doit completer .name (apres status 0)
// status == 4 ? on doit completer .comment (apres status 0)
// status == 5 ? on doit completer .name
// status == 6 ? on doit completer .comment
// status == 7 ? fini

//0->(4)->2->(5)->7
//0->(3)->1->(6)->7
int		update_prog_lengths(t_asm *glob, t_input *input)
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

static int		header_status(int status)
{
	if (status == 0 || status == 2 || status == 3 || status == 5)
		return (print_error(MISSING_NAME, 0));
	return (print_error(MISSING_COMMENT, 0));
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
	else
	{
		if (!complete_header(input, status))
			return (0);
	}
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
		if (status >= 3 && status <= 6)
		{
			if (!(content->bin = ft_strjoin(content->bin, "\n")))
				return (0);
			content->bin_size++;
		}
		if (!update_prog_lengths(glob, content))
			return (0);
		if (status == 7)
			break ;
		*input = (*input)->next;
	}
	return (status == 7);
}
