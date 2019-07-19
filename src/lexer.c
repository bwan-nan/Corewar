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

int			lexer(t_asm *glob, t_list **input)
{
	t_list	*line;
	t_list	*label;
	static int	status = 0;
	// status == 0 ? on accepte les .name et .comment
	// status == 1 ? on accepte .name et pas .comment
	// status == 2 ? on accepte .comment et pas .name
	// status == 3 ? on accepte les instructions et les labels

	line = *input;
	label = glob->labels;
	while (line)
	{
		if (status <= 2)
		{
			if (!check_header(line->content
            , ((t_input *)line->content)->line, &status))
				return (0);
		}
		else
		{
			if (!check_content(glob, &label, line->content
            , ((t_input *)line->content)->line))
				return (0);
		}
		line = line->next;
	}
	fill_queue(glob);
	return (1);
}
