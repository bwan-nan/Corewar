#include "asm.h"

static int		check_length(char *bin, char type)
{
	if (type == 'c')
		if (ft_strlen(bin) > COMMENT_LENGTH)
			return (0);
	if (type == 'n')
		if (ft_strlen(bin) > PROG_NAME_LENGTH))
			return (0);
	return (1);
}

int		       check_header(t_input *input, char *line, int *status)
{
	char		**tab;
	char		*ptr;

	if (!(tab = ft_split_whitespaces(line)))
		return (print_error(MALLOC_ERROR, 0, 0));
	if (tab[0] && (tab[0][0] == '#' || tab[0][0] == ';'))
		return (ret_freetab(1, tab));
	if ((ft_strequ(tab[0], ".name") && *status != 2)
		*status = *status == 0 ? 2 : 3;
	else if (ft_strequ(tab[0], ".comment") && *status != 1))
		*status = *status == 0 ? 1 : 3;
	else
		return (print_error(LEXICAL_ERROR, input->line_number, 1));
	if (tab[1] && tab[1][0] == '"'
	&& (ptr = ft_strchr(&tab[1][1], '"')
    && (!ptr[1] || ptr[1] == '#' || ptr[1] == ';')))
	{
		if (tab[2] && tab[2][0] != ';' && tab[2][0] != '#')
			return (0);
		*ptr = '\0';
		input->bin = ft_strdup(&tab[1][1]);
		input->type = ft_strequ(tab[0], ".name") ? 'n' : 'c';
	}
	else
		print_error(LEXICAL_ERROR, input->line_number);
//	ft_freetab(tab);
	return (check_length(input->bin, input->type));
}
