/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:44:09 by fdagbert          #+#    #+#             */
/*   Updated: 2019/04/11 14:42:30 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# define BUFF_SIZE 1024

# include "libft.h"

typedef struct			s_list
{
	int					fd;
	char				buff[BUFF_SIZE + 1];
	struct s_list		*next;
}						t_list;

int						get_next_line(const int fd, char **line);

#endif
