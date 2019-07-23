/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champion_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:08:47 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/23 02:24:00 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_check_header(t_champ *champ, char *line, t_conf *conf)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	//magic
	ft_memcpy(&champ->magic, line + i++, 1);
	champ->magic = champ->magic << 8;
	ft_memcpy(&champ->magic, line + i++, 1);
	champ->magic = champ->magic << 8;
	ft_memcpy(&champ->magic, line + i++, 1);
	champ->magic = champ->magic << 8;
	ft_memcpy(&champ->magic, line + i++, 1);
	if (champ->magic != COREWAR_EXEC_MAGIC)
		return (-14);
	//name
	while (j < 128)
		champ->name[j++] = line[i++];
	//padding1
	ft_memcpy(&champ->padding1, line + i++, 1);
	champ->padding1 = champ->padding1 << 8;
	ft_memcpy(&champ->padding1, line + i++, 1);
	champ->padding1 = champ->padding1 << 8;
	ft_memcpy(&champ->padding1, line + i++, 1);
	champ->padding1 = champ->padding1 << 8;
	ft_memcpy(&champ->padding1, line + i++, 1);
	if (champ->padding1 != COREWAR_EXEC_PADDING)
		return (-15);
	//inst_size
	ft_memcpy(&champ->inst_size, line + i++, 1);
	champ->inst_size = champ->inst_size << 8;
	ft_memcpy(&champ->inst_size, line + i++, 1);
	champ->inst_size = champ->inst_size << 8;
	ft_memcpy(&champ->inst_size, line + i++, 1);
	champ->inst_size = champ->inst_size << 8;
	ft_memcpy(&champ->inst_size, line + i++, 1);
	if (champ->inst_size > CHAMP_MAX_SIZE)
		return (-12);
	if (!champ->inst_size)
		return (-13);
	//comment
	j = 0;
	while (j < 2048)
		champ->comment[j++] = line[i++];
	//padding2
	ft_memcpy(&champ->padding2, line + i++, 1);
	champ->padding2 = champ->padding2 << 8;
	ft_memcpy(&champ->padding2, line + i++, 1);
	champ->padding2 = champ->padding2 << 8;
	ft_memcpy(&champ->padding2, line + i++, 1);
	champ->padding2 = champ->padding2 << 8;
	ft_memcpy(&champ->padding2, line + i++, 1);
	if (champ->padding2 != COREWAR_EXEC_PADDING)
		return (-15);
	//init_pc
	champ->init_pc = (MEM_SIZE / conf->nb_player);
	champ->init_pc = champ->init_pc * (champ->id - 1);
	return (0);
}

int			ft_check_inst(t_champ *champ, char *line)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = D_HEAD_SIZE;
	while (i < champ->inst_size)
		champ->inst[i++] = line[j++];
	return (0);
}

static void		ft_print_champ(t_champ *champ, t_conf *conf)
{
	int		i;

	i = 0;
	ft_printf("* Joueur %u, avec un poids de %u octets, %s (\"%s\") !\n", champ->id, champ->inst_size, champ->name, champ->comment);
	if (conf->opt[8])
	{
		ft_printf("champ path:%s, fd:%d, id:%u, nb_live:%u, init_pc:%u, magic:%x, pad1:%x, pad2:%x\n", champ->path, champ->fd, champ->id, champ->nb_live, champ->init_pc, champ->magic, champ->padding1, champ->padding2);
	ft_printf("champ inst:\n| ");
		while (i < CHAMP_MAX_SIZE)
		{
			ft_printf("%.2X | ", champ->inst[i]);
			i++;
			if (!(i % D_DEBUG_SIZE))
				ft_printf("\n| ");
		}
		ft_printf("\n\n");
	}
}

int				ft_champion_parser(t_champ *champ, t_conf *conf)
{
	int				ret;
	char			line[D_BIN_MAX_SIZE + 1];

	ret = 0;
	ft_printf("Acclamés par les spectateurs en furie, les champions font leur entrée dans l'arène...\n");
	while (champ)
	{
		ft_bzero(line, D_BIN_MAX_SIZE + 1);
		if ((ret = read(champ->fd, &line, D_BIN_MAX_SIZE)) < 0)
			return (-3);
		//ft_printf("ret:%d\n", ret);
		if (ret > D_BIN_MAX_SIZE)
			return (-11);
		if ((ret = ft_check_header(champ, line, conf)) < 0)
			return (ret);
		if ((ret = ft_check_inst(champ, line)) < 0)
			return (ret);
		ft_print_champ(champ, conf);
		champ = champ->next;
	}
	return (0);
}
