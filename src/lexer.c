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
		ft_printf("PARENT:\nname = %s, byte_nbr = %d\n", parent->name, parent->byte_nbr);
		node = ((t_queue *)elem->content)->node;
		ft_printf("NODE\nname = %s, byte_nbr = %d\n\n", node->line, node->byte_nbr);
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

static int	is_comment(char *line)
{
	int		i;

	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	return (line[i] && (line[i] == '#' || line[i] == ';'));
}

int			lexer(t_asm *glob)
{
	t_list	*input;
	char	*line;
//	t_list	*label;
	int		valid_header;


	valid_header = 0;
	input = glob->input;
	while (input)
	{
	//	ft_putendl(new while iteration in lexer:");
		//ft_putendl(((t_input *)line->content)->line);
		line = ((t_input *)input->content)->line;
		if (!is_comment(line))
		{
			line = ((t_input *)input->content)->line;
			if (!valid_header)
			{
				//ft_putendl(((t_input *)line->content)->line);
				if (!(valid_header = check_header(glob, &input)))
					return (0);
				//ft_putendl(((t_input *)line->content)->bin);
			}
			else
			{
				//ft_putendl(((t_input *)line->content)->line);
				if (!check_content(glob, input->content, line))
					return (0);
			}
			//ft_putendl(((t_input *)line->content)->bin);
		}
		input = input->next;
	}
	//ft_putendl("lexer done");
	fill_queue(glob);
	//ft_putendl("fill queue done");
	return (1);
}
