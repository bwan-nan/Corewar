/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:39:04 by pimichau          #+#    #+#             */
/*   Updated: 2019/07/10 11:41:21 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "libft.h"
# include <stdbool.h>

# define MALLOC_ERROR			"Memory allocation failed."
# define NAME_ERROR				"Champion name too long (Max length 128)."
# define COMMENT_ERROR			"Champion comment too long (Max length 2048)."
# define EMPTY_FILE				"Empty file."
# define SYNTAX_ERROR			"Syntax error"
# define LEXICAL_ERROR			"Lexical error"
# define INVALID_INSTRUCTION	"Invalid instruction"
# define INVALID_LABEL			"Invalid label definition"

typedef struct		s_op
{
	char	name[5];
	int		nb_params;
	char	params_type[3];
	int		id;
	int		cycles;
	char	description[50];
	int		ocp;
	int		carry;
}					t_op;

extern t_op 	op_tab[17];

typedef struct		s_asm
{
	t_list			*input;
	t_list			*labels;
	t_list			*queue;
	char			*ptr;
	char			*ocp_ptr;
	int				byte_nbr;
	int				inst_count;
	int				param;
}					t_asm;

typedef struct		s_label
{
	char			*name;
	int				byte_nbr; //le numero de byte de l'instruction suivante
}					t_label;

typedef struct		s_input
{
	char			*line;
	char			*bin;
	int				bin_size;
	int				op_index;
	int				byte_nbr;
	int				line_number;
	char			type;
	t_label			*label;
	t_list			*previous;
}					t_input;

typedef struct		s_queue
{
	t_input			*node;
	t_label			*parent;
	char			*to_complete;
	int				size;
}					t_queue;

int			get_input(t_asm *glob, t_list **input, char *file);
int			lexer(t_asm *glob, t_list **input);
int			print_error(char *msg, int line_number);

int			update_labels(char *line, t_list **labels);


int			check_content(t_asm *glob, t_list **labels
			, t_input *input, char *line);
int			check_instruction(t_asm *glob, char **tab, t_input *input);
int			check_header(t_input *input, char *line, int *status);
char        **custom_split(char **tab);
int			add_to_queue(t_asm *glob, t_input *input
			, t_label *label, int type);

int		ret_freetab(int ret, char **tab);
#endif
