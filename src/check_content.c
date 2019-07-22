#include "asm.h"

static char		*get_first_word(char *line, int *len)
{
	char	*start;
	int		i;

	//ft_putendl("in get_first_word");
	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	start = &line[i];
	//ft_putendl("start:");
	//ft_putendl(start);
	while (line[i] && line[i] != ':' && line[i] != '#' && line[i] != ';'
	&& !ft_iswhitespace(line[i++]))
		(*len)++;
	//ft_putendl("out of get_first_word");
	return (start);
}

int				check_content(t_asm *glob, t_list **labels
				, t_input *input, char *line)
{
	char		**tab;
	char		*first_word;
	int			len;
	t_label		*label;

	//ft_putendl("line:");
	//ft_putendl(line);
	ft_putendl("check content starts");
	len = 0;
	tab = NULL;
	label = NULL;
	if (*(labels))
		label = (*labels)->content;
	first_word = get_first_word(line, &len);
	if (first_word && first_word[len] && first_word[len] == ':')
	{
		if (label && !ft_strnequ(first_word, label->name, len))
			return (print_error(INVALID_LABEL, input->line_number));
		if (first_word[len + 1]
		&& !(tab = ft_split_whitespaces(&first_word[len + 1])))
			return (print_error(MALLOC_ERROR, 0));
		if (label)
			input->label = label;
		(*labels) = (*labels)->next;
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
	ft_putendl("check content ended");
	return (1);
}
