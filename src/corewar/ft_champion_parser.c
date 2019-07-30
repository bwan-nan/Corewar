/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champion_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:08:47 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/29 16:15:03 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		ft_decode_header(int i, unsigned int *var, char *line)
{
	ft_memcpy(var, line + i++, 1);
	*var = *var << 8;
	ft_memcpy(var, line + i++, 1);
	*var = *var << 8;
	ft_memcpy(var, line + i++, 1);
	*var = *var << 8;
	ft_memcpy(var, line + i++, 1);
	return (i);
}

static int		ft_check_header(int i, t_champ *champ, char *line, t_conf *conf)
{
	int		j;

	i = ft_decode_header(i, &champ->magic, line);
	if (champ->magic != COREWAR_EXEC_MAGIC)
		return (-14);
	j = 0;
	while (j < 128)
		champ->name[j++] = line[i++];
	i = ft_decode_header(i, &champ->padding1, line);
	if (champ->padding1 != COREWAR_EXEC_PADDING)
		return (-15);
	i = ft_decode_header(i, &champ->inst_size, line);
	if (champ->inst_size > CHAMP_MAX_SIZE)
		return (-12);
	if (!champ->inst_size)
		return (-13);
	j = 0;
	while (j < 2048)
		champ->comment[j++] = line[i++];
	i = ft_decode_header(i, &champ->padding2, line);
	if (champ->padding2 != COREWAR_EXEC_PADDING)
		return (-15);
	champ->init_pc = (MEM_SIZE / conf->nb_players);
	champ->init_pc = champ->init_pc * (champ->id - 1);
	return (0);
}

static int		ft_check_inst(t_champ *champ, char *line)
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
	ft_printf("* Joueur %u, avec un poids de %u octets, %s ! (\"%s\")\n",
			champ->id, champ->inst_size, champ->name, champ->comment);
	if (conf->opt[8])
	{
		ft_printf("champ path:%s, fd:%d, id:%u, nb_live:%u, init_pc:%u, \
				magic:%x, pad1:%x, pad2:%x\n",
				champ->path, champ->fd, champ->id, champ->nb_live,
				champ->init_pc, champ->magic, champ->padding1, champ->padding2);
		ft_printf("champ inst:\n| ");
		while (i < CHAMP_MAX_SIZE)
		{
			ft_printf("%.2X | ", champ->inst[i]);
			i++;
			if (!(i % D_GRID_SIZE))
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
	if (!conf->opt[3])
		ft_printf("Acclamés par les spectateurs en furie, les champions font \
				leur entrée dans l'arène...\n");
	while (champ)
	{
		ft_bzero(line, D_BIN_MAX_SIZE + 1);
		if ((ret = read(champ->fd, &line, D_BIN_MAX_SIZE)) < 0)
			return (-3);
		if (ret > D_BIN_MAX_SIZE)
			return (-11);
		if ((ret = ft_check_header(0, champ, line, conf)) < 0)
			return (ret);
		if ((ret = ft_check_inst(champ, line)) < 0)
			return (ret);
		if (!conf->opt[8] && !conf->opt[3])
			ft_print_champ(champ, conf);
		champ = champ->next;
	}
	return (0);
}
