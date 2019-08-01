/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:39:04 by pimichau          #+#    #+#             */
/*   Updated: 2019/08/01 16:25:04 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op_asm.h"
# include "libft.h"
# include <stdbool.h>
# include <fcntl.h>

# define MALLOC_ERROR			"Memory allocation failed."
# define NAME_ERROR				"Champion name too long (Max length 128)."
# define COMMENT_ERROR			"Champion comment too long (Max length 2048)."
# define EMPTY_FILE				"Empty file."
# define SYNTAX_ERROR			"Syntax error"
# define LEXICAL_ERROR			"Lexical error"
# define INVALID_INSTRUCTION	"Invalid instruction"
# define INVALID_LABEL			"Invalid label definition"
# define INVALID_PARAMS			"Invalid parameters definition"
# define MISSING_NAME			"Missing or incomplete program name."
# define MISSING_COMMENT		"Missing or incomplete program comment."
# define NO_INST				"Missing instructions."
# define MAN_PATH				"src/man/man.txt"

typedef struct		s_op
{
	char			name[5];
	int				nb_params;
	char			params_type[3];
	int				id;
	int				cycles;
	char			description[50];
	int				ocp;
	int				carry;
}					t_op;

extern t_op			g_op_tab[17];

typedef struct		s_asm
{
	t_list			*input;
	t_list			*labels;
	t_list			*current_label;
	t_list			*queue;
	char			*ptr;
	char			*ocp_ptr;
	int				byte_nbr;
	int				inst_count;
	int				param;
	int				check;
	int				name_length;
	int				comment_length;
}					t_asm;

typedef struct		s_label
{
	char			*name;
	int				byte_nbr;
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
}					t_input;

typedef struct		s_queue
{
	t_input			*node;
	t_label			*parent;
	char			*to_complete;
	int				size;
}					t_queue;

int					file_exists(char *file);
char				*get_file_name(char *str);
int					get_input(t_list **input, char *file);
int					lexing(t_asm *glob);
int					print_error(char *msg, int line_number);

int					update_labels(t_asm *glob, t_list *input, t_list **labels);

int					check_content(t_asm *glob, t_input *input, char *line);
int					check_instruction(t_asm *glob, char **tab, t_input *input);
int					check_header(t_asm *glob, t_list **input);
char				**custom_split(char **tab);
int					add_to_queue(t_asm *glob, t_input *input
					, t_label *label, int type);
int					fill_queue(t_asm *glob);
void				reorder_list(t_list **list);
int					create_cor_file(t_asm *glob, char *file);

int					is_empty(char *line);
int					is_comment(char *line);

void				update_ocp(t_asm *glob, t_input *input, char type);
int					is_instruction(char *str);
int					ft_isnumber(char *str);
int					ft_isdigits(char *str);
t_label				*is_label(char *str, t_list *label);
void				write_binary(t_asm *glob, int op_index
					, char *byte, int type);
int					check_register(t_asm *glob, t_input *input, char *str);
int					check_direct(t_asm *glob, t_input *input, char *str);
int					check_indirect(t_asm *glob, t_input *input, char *str);
int					check_param(t_asm *glob, char *str
					, char type, t_input *input);
int					check_params(t_asm *glob, char **tab
					, t_op op, t_input *input);
int					check_after_quote(char *line, int n);
int					check_before_quote(t_input *input, char *line
					, int n, int *status);
void				update_status(char *type, int *status);
int					header_status(int status);

int					free_program(t_asm *glob, int ret);
int					is_asm_file(char *name);
int					print_error(char *error_msg, int line_number);
#endif
