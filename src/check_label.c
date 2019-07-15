#include "asm.h"

static int      check_label_chars(char *label)
{
    int     i;

    i = 0;
    while (label[i])
    {
        if (!ft_strchr(LABEL_CHARS, label[i]))
            return (0);
        i++;
    }
    return (1);
}

static int		is_instruction(char *str)
{
	int	i;

	i = 0;
	while (op_tab[i])
	{
		if (ft_strequ(op_tab[i][0], str))
			return (i);
		i++;
	}
	return (0);
}

int             get_tab_len(char **tab)
{
    int     i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

static int      check_param(char *str, char type)
{
    //verifier si "r1" est bien un T_REG, %:label un T_DIR, etc...

    //faire une liste de labels et checker si on appelle bien un label existant
}


static int      check_params(char **tab, t_op op)
{
    char    **param_tab;
	int		j;
    int     k;

	j = 0;
	if (!(param_tab = custom_split(tab)))
        return (0);
    if (get_tab_len(param_tab) != op.nb_params * 2 - 1)
        return (0);
    k = 0;
	while (j <  op.nb_params * 2 - 1)
	{
		if (j % 2 && !ft_strequ(param_tab[j], ","))
			return (0);
		else if (!check_param(param_tab[j], op.params_type[k]))
		{
			k++;
			return (0);
        }
		j++;
	}
}

static int		check_instr(char **tab, t_input *input)
{
	int	index;

	index = 0;
	if (tab[0] && (tab[0][0] == '#' || tab[0][0] == ';'))
		return (1);
	if (!(index = is_instruction(tab[0])))
		return (0);
	if (!tab[1] || !check_params(tab + 1, op_tab[index]))
		return (0);

}

int		       check_label(t_input *input, char *line)
{
	char	**tab;
	char	*ptr;

	if (!(tab = ft_split_whitespaces(line)))
		return (print_error(MALLOC_ERROR, 0));
	if (tab[0] && ((ptr = ft_strchr(tab[0], LABEL_CHAR)) && !ptr[1]))
    {
		if (!check_label_chars(tab[0]))
			return (print_error(LEXICAL_ERROR, input->line_number)); //freetab...
		if (tab[1])
			if (!check_instr(tab + 1, input))
				return (print_error(INVALID_INSTRUCTION, input->line_number)); //freetab...
    }
	else
	{
		if (!check_instr(tab, input))
			return (print_error(INVALID_INSTRUCTION, input->line_number)); //freetab partout
	}
    //ft_freetab()
	return (1);
}
