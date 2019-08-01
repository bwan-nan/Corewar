/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_asm_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:28:46 by pimichau          #+#    #+#             */
/*   Updated: 2019/07/31 13:28:48 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_asm_file(char *name)
{
	char	*ext;

	ext = ft_strrchr(name, '.');
	if (!ft_strequ(ext, ".s"))
		return (0);
	return (1);
}
