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

# define MALLOC_ERROR			"Memory allocation failed."
# define NAME_ERROR				"Champion name too long (Max length 128)."
# define COMMENT_ERROR			"Champion comment too long (Max length 2048)."
# define FILE_EMPTY				"Empty file."
# define LEXICAL_ERROR			"Lexical error"
# define INVALID_INSTRUCTION	"Invalid instruction"

typedef struct		s_op
{
	char	name[5];
	int		nb_params;
	char	params_type[3];
	int		id;
	int		cycles;
	char	description[50];
	int		octal;
	int		label_size;
}					t_op;

typedef struct		s_asm
{
	t_list			*input;
}					t_asm;

typedef struct		s_input
{
	char			*line;
	char			*bin;
	int				line_number;
	char			type;
}					t_input;

#endif
