#include "asm.h"

static int		check_length(char *bin, char type)
{
	if (type == 'c')
		if (ft_strlen(bin) > COMMENT_LENGTH)
			return (0);
	if (type == 'n')
		if (ft_strlen(bin) > PROG_NAME_LENGTH)
			return (0);
	return (1);
}

static int		check_before_quote(t_input *input, char *line, int n, int *status)
{
	char		*str;

	if (!(str = ft_trim(ft_strsub(line, 0, n))))
		return (0);
	if (ft_strequ(str, ".name") && *status != 2)
		*status = *status == 0 ? 2 : 3;
	else if (ft_strequ(str, ".comment") && *status != 1)
		*status = *status == 0 ? 1 : 3;
	else
		return (0);//free str
	input->type = ft_strequ(str, ".name") ? 'n' : 'c';
	ft_strdel(&str);
	return (1);//ret_freetab
}

static int		check_after_quote(char *line, int n)
{
	char	**tab;

	if (line[n + 1])
	{
		if (!(tab = ft_split_whitespaces(line + n + 1)))
			return (0);
		if (tab[0] && !(tab[0][0] == '#' || tab[0][0] == ';'))
			return (0); //ret_freetab
	}
	return (1);//ret_freetab
}

static int		check_validity(t_input *input, char *line, int *status)
{
	int	first;
	int	second;

	if ((first = ft_strnchr_index(line, 1, '"')) != -1
	&& (second = ft_strnchr_index(line, 2, '"')) != -1)
	{
		if (check_before_quote(input, line, first, status)
		&& check_after_quote(line, second))
		{
			if (!(input->bin = ft_strsub(line, first + 1, second - first - 1)))
				return (0);
			input->bin_size = ft_strlen(input->bin);
			//ft_putendl(input->bin);
			return (1);
		}
	}
	return (print_error(LEXICAL_ERROR, input->line_number));
}

int		       check_header(t_input *input, char *line, int *status)
{
	if (!check_validity(input, line, status))
		return (0);
	return (check_length(input->bin, input->type));
}
