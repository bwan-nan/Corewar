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

int             get_tab_len(char **tab)
{
    int     i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

static int		ft_isnumber(char *str)
{
	int					i;
	char				cpy[21];
	unsigned long long	nb;

	if (!str)
		return (0);
	if (*str == '-')
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

static int      check_param(t_asm *glob, char *str, char type, t_input *input)
{
	if (*str == 'r' && (type & T_REG))
		if (ft_strlen(str) <= 3 && str[1] && ft_isdigits(&str[1]))
			get_binary(input, T_REG); //-> update input->bin
	else if (*str == '%' && (type & T_DIR))
	{
		//%:label , %1, %-1
		if (str[1] == ":")
		{
			// verif appartient a glob->labels
		}
		else if (str[1] == '+' || !ft_isinteger(str + 1))
			return (print_error(SYNTAX_ERROR, input->line_number));
	}
	else if ((*str == ':' || ft_isnumber(str)) && (type & T_IND))
	{
		:live, 4, -4
	}
	else
		return (print_error(SYNTAX_ERROR, input->line_number));
	//instr + OCP (si requis) + params a stocker dans input->bin apres les avoir traduit...
	return (1);
}


static int      check_params(t_asm *glob, char **tab, t_op op, t_input *input)
{
	int		j;
    int     k;

	j = 0;
    if (get_tab_len(tab) != op.nb_params * 2 - 1)
        return (0);
    k = 0;
	while (j <  op.nb_params * 2 - 1)
	{
		if (j % 2 && !ft_strequ(tab[j], ","))
			return (0);
		else if (!check_param(tab[j], op.params_type[k++], input))
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
	if (!param_tab[1] || !check_params(glob, param_tab + 1
	, op_tab[index], input))
		return (0);

}
