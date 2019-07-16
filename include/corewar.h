/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:48:51 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/16 18:24:15 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# define D_OPT_MAX 8
# define D_OP_MAX 17
# define D_MAN_PATH "./src/man/man_cor"

# include "ft_printf.h"
# include "op.h"

typedef struct			s_champ
{
	char				*path;
	int					fd;
	unsigned int		id;
	unsigned int		pc;
	unsigned int		magic;
	unsigned int		prog_size;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	char				inst[CHAMP_MAX_SIZE + 1];
	struct s_champ		*next;
}						t_champ;

typedef struct			s_conf
{
	int					opt[D_OPT_MAX];
	int					grid[MEM_SIZE];
	const t_op				*op_tab;
}						t_conf;

void					ft_init_op(t_conf *conf);

#endif
