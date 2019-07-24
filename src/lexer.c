#include "asm.h"

static void fill_queue(t_asm *glob)
{
	t_list		*elem;
	t_label		*parent;
	t_input		*node;
	int			relative_address;
	char		*byte;

	elem = glob->queue;
	while (elem)
	{
		parent = ((t_queue *)elem->content)->parent;
		node = ((t_queue *)elem->content)->node;
		relative_address = parent->byte_nbr - node->byte_nbr;
		byte = (char *)(&relative_address);
		if (((t_queue *)elem->content)->size == 4)
		{
			*(((t_queue *)elem->content)->to_complete++) = *(byte + 3);
			*(((t_queue *)elem->content)->to_complete++) = *(byte + 2);
		}
		*(((t_queue *)elem->content)->to_complete++) = *(byte + 1);
		*(((t_queue *)elem->content)->to_complete) = *byte;
		elem = elem->next;
	}
}

int		is_empty(char *line)
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

int	is_comment(char *line)
{
	int		i;

	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	return (line[i] && (line[i] == '#' || line[i] == ';'));
}
/*
static void print_labels(t_list *labels)
{
	t_label *label;
	while (labels)
	{
		label = ((t_label *)labels->content);
		ft_putendl(label->name);
		labels = labels->next;
	}
}
*/
int			lexer(t_asm *glob)
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
			line = ((t_input *)input->content)->line;
			if (!valid_header)
			{
				if (!(valid_header = check_header(glob, &input)))
					return (0);
				if (!update_labels(glob, input->next, &glob->labels))
					return (print_error(MALLOC_ERROR, 0));
			}
			else
			{
				//ft_putendl(line);
				if (!check_content(glob, input->content, line))
					return (0);
			}
		}
		input = input->next;
	}
	fill_queue(glob);
	return (1);
}
