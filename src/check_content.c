#include "asm.h"

/*static int      check_label_chars(char *label, int stop)
{
    int     i;

    i = 0;
    while (label[i] && i < stop)
    {
        if (!ft_strchr(LABEL_CHARS, label[i]))
            return (0);
        i++;
    }
    return (1);
}*/

//on passe les espaces du debut, puis on verifie qu'on a un ":"
//et que la chaine de caratere qui precede ce ":" est en LABEL_CHARS,
//si oui on ft_split_whitespaces a partir du caractere suivant le ":"
//si non on ft_split_whitespaces la line initiale

/*
test1:
test2:
test3:
	live %1
...

		step 1: on trouve le premier mot de line
		step 2: si le premier mot se termine par un ":"
					si ca ne matche pas avec label->name on return error
					sinon on tab = ft_split_whitespaces(&":" + 1) && on avance label = label->next
				sinon ->ft_split_whitespaces(line) //check_instruction (on est pas sur un label mais sur une instruction seule)
		step 3: si instruction valide (2 possibilités):
					- soit c'est une instruction sans label en debut de fichier (cad label pointe sur la tete de la liste)
					- soit elle appartient à un OU plusieurs labels
						-> on update l'adresse du/des labels dont le byte_nbr == 0
				sinon:
					return error
*/
static char		*get_first_word(char *line, int *len)
{
	char	*start;

	while (ft_iswhitespace(*line))
		line++;
	start = line;
	while (*line && *line != ':' && *line != '#' && *line != ';'
	&& !ft_iswhitespace(line++))
		(*len)++;
	return (start);
}

int				check_content(t_asm *glob, t_list **labels
				, t_input *input, char *line)
{
	char		**tab;
	char		*first_word;
	int			len;
	t_label		*label;

	len = 0;
	tab = NULL;
	label = (t_label *)labels->content;
	first_word = get_first_word(line, &len);
	if (first_word[len] && first_word[len] == ':')
	{
		if (!ft_strnequ(first_word, label->name, len))
			return (print_error(INVALID_LABEL, input->line_number));
		if (first_word[len + 1]
		&& !(tab = ft_split_whitespaces(&first_word[len + 1])))
			return (print_error(MALLOC_ERROR, 0));
		input->label = (*labels);
		(*labels) = (*labels)->next;
	}
	else
		if (!(tab = ft_split_whitespaces(line)))
			return (print_error(MALLOC_ERROR, 0));
	if (tab && tab[0])
		if (!check_instruction(glob, tab, input))
			return (print_error(INVALID_INSTRUCTION, input->line_number));
	//freetab...
	return (1);
}
