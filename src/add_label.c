#include "asm.h"

static int	add_label(t_list **labels, char *line, int start, int len)
{
	t_label		new;
	t_list		*node;

	new.name = NULL;
	new.byte_nbr = -1;
	if (!(node = ft_lstnew(&new, sizeof(t_label))))
		return (0);
	((t_label *)node->content)->name = ft_strsub(line, start, len);
	ft_lstappend(labels, node);
	return (1);
}

int			update_labels(char *line, t_list **labels)
{
    int     i;
    int     j;
	int		label_char_index;

    i = 0;
	while (ft_iswhitespace(line[i]))
        i++;
    j = 0;
	while (ft_strchr(LABEL_CHARS, line[i + j]))
		j++;
	if (line[i + j] == ':')
		return (add_label(labels, line, i, j));
	return (1);
}
