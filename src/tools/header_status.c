/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:52:04 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/31 13:18:40 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	update_status(char *type, int *status)
{
	if (*status == 3)
	{
		*type = 'N';
		*status = 1;
	}
	else if (*status == 4)
	{
		*type = 'C';
		*status = 2;
	}
	else if (*status == 5 || *status == 6)
	{
		*type = *status == 5 ? 'N' : 'C';
		*status = 7;
	}
}

int		header_status(int status)
{
	if (status == 7)
		return (1);
	if (status == 0 || status == 2 || status == 3 || status == 5)
		return (print_error(MISSING_NAME, 0));
	return (print_error(MISSING_COMMENT, 0));
}
