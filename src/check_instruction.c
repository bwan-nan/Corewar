#include "asm.h"

static int		is_instruction(char *str)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		if (ft_strequ(op_tab[i].name, str))
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

	if (!str || (*str == '-' && call > 0))
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
	call = 0;
	return (1);
}

static int		ft_isdigits(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static t_label		*is_label(char *str, t_list *label)
{
	while (label)
	{
		if (ft_strequ(str, ((t_label *)label->content)->name))
			return (label->content);
		label = label->next;
	}
	return (NULL);
}

static				void update_ocp(t_asm *glob, t_input *input, char type)
{
	if (op_tab[input->op_index].ocp)
	{
		if (type & T_REG)
			*(glob->ptr++) |= REG_CODE << (8 - 2 * glob->param);
		else if (type & T_DIR)
	 		*(glob->ptr++) |= DIR_CODE << (8 - 2 * glob->param);
		else if (type & T_IND)
			*(glob->ptr++) |= IND_CODE << (8 - 2 * glob->param);
	}
}

static int			check_register(t_asm *glob, t_input *input, char *str)
{
	if (ft_strlen(str) > 3 || !str[1] || !ft_isdigits(&str[1]))
	{
		//ft_putendl("check register");
		return (print_error(SYNTAX_ERROR, input->line_number));
	}
	update_ocp(glob, input, T_REG);
	*(glob->ptr++) = ft_atoi(str + 1);
	glob->byte_nbr++;
	return (1);
}

//nbr_byte du label - nbr_byte de l'instruction actuelle
static void			write_binary(t_asm *glob, int op_index
					, char *byte, int type)
{
	if ((op_index < 8 || op_index == 12) && (type & T_DIR))
	{
		*(glob->ptr++) = *(byte + 3);
		*(glob->ptr++) = *(byte + 2);
	}
	*(glob->ptr++) = *(byte + 1);
	*(glob->ptr++) = *byte;
}

static void			update_label_binary(t_asm *glob, t_input *input
					, int address, int type)
{
	int			relative_address;
	char		*byte;

	if (input->label)
	{
		relative_address = address - input->label->byte_nbr;
		byte = (char *)(&relative_address);
		write_binary(glob, input->op_index, byte, type);
	}
}

static int			check_direct(t_asm *glob, t_input *input, char *str)
{
	t_label		*label;
	int			address;

	if (str[1] == ':')
	{
		if (!str[2] || !(label = is_label(&str[2], glob->labels)))
		{
			//ft_putendl("check direct -> label");
			return (print_error(SYNTAX_ERROR, input->line_number));
		}
		if (label->byte_nbr != -1)
			update_label_binary(glob, input, label->byte_nbr, T_DIR);
		else
			add_to_queue(glob, input, label, T_DIR);
	}
	else if (str[1] && ft_isnumber(&str[1]))
	{
		address = ft_atoi(&str[1]);
		write_binary(glob, input->op_index, (char *)(&address), T_DIR);
	}
	else
	{
		//ft_putendl("else check direct");
		return (print_error(SYNTAX_ERROR, input->line_number));
	}
	update_ocp(glob, input, T_DIR);
	glob->byte_nbr += (input->op_index < 8 || input->op_index == 12) ? 4 : 2;
	return (1);
}

static int			check_indirect(t_asm *glob, t_input *input, char *str)
{
	t_label		*label;
	int			address;
	int ret;

	if (str[0] == ':')
	{
		if (!(label = is_label(&str[1], glob->labels)))
		{
			//ft_putendl("check indirect -> label");
			return (print_error(SYNTAX_ERROR, input->line_number));
		}
		if (label->byte_nbr != -1)
			update_label_binary(glob, input, label->byte_nbr, T_IND);
		else
			add_to_queue(glob, input, label, T_IND);
	}
	else if (str[0] && (ret = ft_isnumber(str)))
	{
		address = ft_atoi(str);
		write_binary(glob, input->op_index, (char *)(&address), T_IND);
	}
	else
	{
		//ft_putnbrendl(ret);
		//ft_putendl(str);
		//ft_putendl("else check indirect");
		return (print_error(SYNTAX_ERROR, input->line_number));
	}
	update_ocp(glob, input, T_IND);
	glob->byte_nbr += 2;
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
	{
		//ft_putendl(str);
		//ft_putendl("check param");
		return (print_error(SYNTAX_ERROR, input->line_number));
	}
	//get_binary(input, T_REG); //-> update input->bin
	//instr + OCP (si requis) + params a stocker dans input->bin apres les avoir traduit...
	return (1);
}

static int      check_params(t_asm *glob, char **tab, t_op op, t_input *input)
{
	int			j;

 	if (get_tab_len(tab) != op.nb_params * 2 - 1)
    	return (0);
 	glob->param = 0;
	glob->byte_nbr += op_tab[input->op_index].ocp;
	j = 0;
	//ft_show_tab(tab);
	while (j <  op.nb_params * 2 - 1)
	{
		if (j % 2)
		{
			if (!ft_strequ(tab[j], ","))
				return (0);
		}
		else if (!check_param(glob, tab[j], op.params_type[(glob->param)++], input))
			return (0);
		j++;
	}
	return (1);
}

int			check_instruction(t_asm *glob, char **tab, t_input *input)
{
	char			**param_tab;

	ft_putendl("check_instruction begins");
	if (input && input->label)
		input->label->byte_nbr = glob->byte_nbr;
	input->byte_nbr = glob->byte_nbr;
	if (tab[0] && (tab[0][0] == '#' || tab[0][0] == ';'))
		return (1);
	//ft_printf("{green}");
	//ft_show_tab(tab);
	if (!(param_tab = custom_split(tab)))
		return (0);
	//ft_printf("{red}");
	//ft_show_tab(param_tab);
	//ft_printf("{nc}");
	//freetab(tab);
	if ((input->op_index = is_instruction(param_tab[0])) == -1)
		return (0);
	glob->byte_nbr++;
	if (!(input->bin = ft_strnew(11)))
		return (0);
	glob->ptr = input->bin;
	*(glob->ptr++) = (op_tab[input->op_index].id);
	if (!param_tab[1]
	|| !check_params(glob, param_tab + 1, op_tab[input->op_index], input))
		return (0);
	input->bin_size = glob->byte_nbr - input->byte_nbr;
	ft_putendl("check_instruction ends");
	return (1);
}
