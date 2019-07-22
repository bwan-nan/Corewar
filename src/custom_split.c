#include "asm.h"

static int  count_params(char **tab)
{
    int     i;
	int		j;
    int     num_params;
	int		len;

    num_params = 0;
	len = 0;
    i = 0;
    while (tab[i])
    {
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == ',' || (tab[i][j] == '%' && len))
			{
				len = 0;
				num_params++;
			}
			else if (tab[i][j] == '#' || tab[i][j] == ';')
				return (num_params);
        	else if (++len == 1)
				num_params++;
			j++;
		}
		i++;
		len = 0;
    }
    return (num_params);
}

static int	add_word(char **tab, char **param_tab, int *word_index, int params_count)
{
    char    *str;
    int     i;
    int     len;

    str = *tab;
    i = 0;
    while (str && str[i])
    {
        len = 0;
        while (str[i + len] && ((!ft_strchr(",;#%", str[i + len]) && len != 0)
		|| (!ft_strchr(",;#", str[i + len]) && len == 0)))
            len++;
        if (len == 0 && str[i] == ',')
		{
            if (!(param_tab[(*word_index)++] = ft_strdup(",")))
				return (0);
		}
        else
        {
            if (!(param_tab[(*word_index)++] = ft_strsub(str, i, len)))
				return (0);
            i += len - 1;
        }
		if (*word_index == params_count)
			return (1);
        i++;
    }
    if (tab[1])
        return (add_word(tab + 1, param_tab, word_index, params_count));
	return (1);
}

char        **custom_split(char **tab)
{
    int		len;
	char	**param_tab;
    int     word_index;

    len = count_params(tab);
    word_index = 0;
    param_tab = NULL;
    if (!(param_tab = (char **)malloc(sizeof(char *) * (len + 1))))
        return (NULL);
    param_tab[len] = 0;
    if (!add_word(tab, param_tab, &word_index, len))
	{
		ft_freetab(param_tab);
        return (NULL);
	}
    return (param_tab);
}
//KO
//"r1,r2,,r3"
//",r1,r2 r3"
//"r1,#com,ment r2, r3"
//"test, ,%2, 1"
//"test, ,%2 , 1"
//"test, ,%2 ,1"
//",test, %2 ,1"
//"test, %2 ,1,"

//OK
//"r1,r2, r3"
//"r1, r2, r3#com,ment"
//"r1, r2, r3;com,ment"
//"r1,r2,r3;com,ment"
//"r1,r2,r3;#com,ment"
//"r1,r2,r3"
//"r1#com,ment"
