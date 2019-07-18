int		lexer(t_asm *glob, t_list **input)
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
			if (!check_header(line->content
            , ((t_input *)line->content)->line, &status))
				return (1);
		else
			if (!check_content(glob, &label, line->content
            , ((t_input *)line->content)->line))
				return (1);
		line = line->next;
	}
}
