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
	return (line[i] == '#' || line[i] == ';');
}

int			lexer(t_asm *glob)
{
	t_list	*line;
//	t_list	*label;
	static int	status = 0;
	// status == 0 ? on accepte les .name et .comment
	// status == 1 ? on accepte .name et pas .comment
	// status == 2 ? on accepte .comment et pas .name
	// status == 3 ? on accepte les instructions et les labels

	line = glob->input;
	while (line)
	{
	//	ft_putendl(new while iteration in lexer:");
		//ft_putendl(((t_input *)line->content)->line);
		if (!is_comment(((t_input *)line->content)->line))
		{
			if (status <= 2)
			{
				//ft_putendl(((t_input *)line->content)->line);
				if (!check_header(line->content
            	, ((t_input *)line->content)->line, &status))
					return (0);
				//ft_putendl(((t_input *)line->content)->bin);
			}
			else
			{
				//ft_putendl(((t_input *)line->content)->line);
				if (!check_content(glob, line->content
				, ((t_input *)line->content)->line))
					return (0);
			}
			//ft_putendl(((t_input *)line->content)->bin);
		}
		line = line->next;
	}
	//ft_putendl("lexer done");
	fill_queue(glob);
	//ft_putendl("fill queue done");
	return (1);
}
