#include "asm.h"

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
	return (-1);
}

static int		ft_isnumber(char *str)
{
	int									i;
	char								cpy[21];
	unsigned long long	nb;
	static int					call = 0;

	if (!str || ((*str == '-' || *str == '+') && call > 0))
		return (0);
	else if (*str == '-' && call++ == 0)
		return (ft_isnumber(str + 1));
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	if (i > 20)
		return (0);
	if (i == 20)
	{
		ft_strcpy(cpy, str);
		cpy[19] = '\0';
		if ((nb = ft_atoull(cpy)) > 1844674407370955161)
			return (0);
		else if (nb == 1844674407370955161 && str[19] > '5')
			return (0);
	}
	return (1);
}

int		ft_isdigits(char *str)
{
	while (*str)
	(
		if (!ft_isdigit(*str))
			return (0);
		str++;
	)
	return (1);
}

static int			is_label(char *str, t_list *labels)
{
	while (labels)
	{
		if (ft_strequ(str, ((t_label *)labels->content)->name))
			return (1);
		labels = labels->next;
	}
	return (0);
}

static					void update_ocp(t_asm *glob, t_input *input, char type)
{
	if (glob->ocp == true)
	{
		if (type & T_REG)
			input->bin[1] |= REG_CODE << (8 - 2 * glob->param);
		else if (type & T_DIR)
	 		input->bin[1] |= DIR_CODE << (8 - 2 * glob->param);
		else if (type & T_IND)
			input->bin[1] |= IND_CODE << (8 - 2 * glob->param);
	}
}

static int			check_register(t_asm *glob, t_input *input, char *str)
{
	if (ft_strlen(str) > 3 || !str[1] || ft_isdigits(&str[1])
		return (print_error(SYNTAX_ERROR, input->line_number));
	update_ocp(glob, input, T_REG);
	return (1);
}

static int			check_direct(t_asm *glob, t_input *input, char *str)
{
	if (str[1] == ':')
		if (!str[2] || !is_label(&str[2], glob->labels))
			return (print_error(SYNTAX_ERROR, input->line_number));
	else if (!ft_isnumber(&str[1]))
		return (print_error(SYNTAX_ERROR, input->line_number));
	update_ocp(glob, input, T_DIR);
	return (1);
}

static int			check_indirect(t_asm *glob, t_input *input, char *str)
{
	if (str[0] == ":" && !ft_islabel(&str[1], glob->labels))
		return (print_error(SYNTAX_ERROR, input->line_number));
	else if (!ft_isnumber(str))
		return (print_error(SYNTAX_ERROR, input->line_number));
	update_ocp(glob, input, T_IND);
	return (1);
}

static int      check_param(t_asm *glob, char *str, char type, t_input *input)
{
	if (*str == 'r' && (type & T_REG))
		return (check_register(glob, input, str));
	else if (*str == '%' && (type & T_DIR))
		return (check_direct(glob, input, str)); 	//%:label , %1, %-1
	else if (type & T_IND)
		return (check_indirect(glob, input, str));//:live, 4, -4
	else
		return (print_error(SYNTAX_ERROR, input->line_number));
	//get_binary(input, T_REG); //-> update input->bin
	//instr + OCP (si requis) + params a stocker dans input->bin apres les avoir traduit...
	return (1);
}

static int      check_params(t_asm *glob, char **tab, t_op op, t_input *input)
{
	int		j;

	glob->ocp = 0;
  if (get_tab_len(tab) != op.nb_params * 2 - 1)
      return (0);
  glob->param = 1;
	j = 0;
	while (j <  op.nb_params * 2 - 1)
	{
		if (j % 2 && !ft_strequ(tab[j], ","))
			return (0);
		else if (!check_param(glob, tab[j], op.params_type[(glob->param)++], input))
			return (0);
		j++;
	}
}

int			check_instruction(t_asm *glob, char **tab
			, t_input *input, t_list *parent)
{
	char	**param_tab;
	int		index;

	index = 0;
	if (tab[0] && (tab[0][0] == '#' || tab[0][0] == ';'))
		return (1);
	if (!(param_tab = custom_split(tab)))
		return (0);
	//freetab(tab);
	if ((index = is_instruction(param_tab[0])) == -1)
		return (0);
	if (!(input->bin = ft_strnew(11)))
		return (0);
	*(input->bin) = op_tab[index][3];
	glob->ocp = op_tab[index][6] ? true : false;
	if (!param_tab[1] || !check_params(glob, param_tab + 1
	, op_tab[index], input))
		return (0);

}
