/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:54:15 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/08/01 15:18:57 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include "get_next_line.h"
# include "output.h"
# include "strings.h"
# include "memory.h"
# include "lists.h"
# include "conversions.h"
# include "binary.h"
# include "ft_printf.h"
# include <stdlib.h>

void				ft_show_tab(char **tab);
float				ft_power(float nb, int exp);
void				sort_int_tab(int *tab, unsigned int size);
int					ft_max(int a, int b);
int					ft_sqrt(int nb);
int					get_tab_len(char **tab);
long long			ft_recursive_power(long long nb, int power);
void				ft_freetab(char **tab);
int					ret_freetab(char **tab, int ret);

#endif
