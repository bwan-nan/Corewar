/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champion_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:08:47 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/18 14:50:58 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_check_header(t_champ *champ, unsigned char *line, t_conf *conf)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	ft_memcpy(&champ->magic, line + i++, 1);
	champ->magic = champ->magic << 8;
	ft_memcpy(&champ->magic, line + i++, 1);
	champ->magic = champ->magic << 8;
	ft_memcpy(&champ->magic, line + i++, 1);
	champ->magic = champ->magic << 8;
	ft_memcpy(&champ->magic, line + i++, 1);
	ft_printf("magic:%d %x\n", champ->magic, champ->magic);
	if (champ->magic != COREWAR_EXEC_MAGIC)
		return (-14);
	while (j < 128)
		champ->name[j++] = line[i++];
	ft_memcpy(&champ->padding1, line + i++, 1);
	champ->padding1 = champ->padding1 << 8;
	ft_memcpy(&champ->padding1, line + i++, 1);
	champ->padding1 = champ->padding1 << 8;
	ft_memcpy(&champ->padding1, line + i++, 1);
	champ->padding1 = champ->padding1 << 8;
	ft_memcpy(&champ->padding1, line + i++, 1);
	ft_printf("pad1:%d %x\n", champ->padding1, champ->padding1);
	if (champ->padding1 != COREWAR_EXEC_PADDING)
		return (-15);
	ft_memcpy(&champ->inst_size, line + i++, 1);
	champ->inst_size = champ->inst_size << 8;
	ft_memcpy(&champ->inst_size, line + i++, 1);
	champ->inst_size = champ->inst_size << 8;
	ft_memcpy(&champ->inst_size, line + i++, 1);
	champ->inst_size = champ->inst_size << 8;
	ft_memcpy(&champ->inst_size, line + i++, 1);
	ft_printf("inst_size:%d %x\n", champ->inst_size, champ->inst_size);
	//if (champ->inst_size > CHAMP_MAX_SIZE)
	//	return (-12);
	if (!champ->inst_size)
		return (-13);
	j = 0;
	while (j < 2048)
		champ->comment[j++] = line[i++];
	ft_memcpy(&champ->padding2, line + i++, 1);
	champ->padding2 = champ->padding2 << 8;
	ft_memcpy(&champ->padding2, line + i++, 1);
	champ->padding2 = champ->padding2 << 8;
	ft_memcpy(&champ->padding2, line + i++, 1);
	champ->padding2 = champ->padding2 << 8;
	ft_memcpy(&champ->padding2, line + i++, 1);
	ft_printf("pad2:%d %x\n", champ->padding2, champ->padding2);
	if (champ->padding2 != COREWAR_EXEC_PADDING)
		return (-15);
	champ->init_pc = (MEM_SIZE / conf->nb_player);
	champ->init_pc = champ->init_pc * (conf->nb_player - champ->id);
	return (0);
}

int			ft_check_inst(t_champ *champ, unsigned char *line)
{
	//ft_memcpy(champ->inst, line + D_HEAD_SIZE, champ->inst_size);
	ft_memcpy(champ->inst, line + D_HEAD_SIZE, CHAMP_MAX_SIZE);
	return (0);
}

static void		ft_print_champ(t_champ *champ)
{
	int		i;

	i = 0;
	ft_printf("champ path:%s, fd:%d, id:%u, nb_live:%u, init_pc:%u, inst_size:%u, magic:%x, pad1:%x, pad2:%x, name:%s, comment:%s\n", champ->path, champ->fd, champ->id, champ->nb_live, champ->init_pc, champ->inst_size, champ->magic, champ->padding1, champ->padding2, champ->name, champ->comment);
	ft_printf("champ inst: ");
	while (i < CHAMP_MAX_SIZE)
	{
		ft_printf("%x | ", champ->inst[i]);
		i++;
	}
	ft_printf("\n\n");
}

/*static int		ft_check_base(unsigned char *line)
{
	ft_printf("len:%d, line:%s\n", ft_strlen((char *)line), line);
	return (0);
}*/

int				ft_champion_parser(t_champ *champ, t_conf *conf)
{
	int				ret;
	//unsigned char	line[D_BIN_MAX_SIZE + 1];
	unsigned char	line[1000000];

	ret = 0;
	while (champ)
	{
		//ft_bzero(line, D_BIN_MAX_SIZE + 1);
		ft_bzero(line, 1000000);
		if ((ret = read(champ->fd, &line, D_BIN_MAX_SIZE)) < 0)
			return (-3);
		/*int i = 0;
		while (i < D_BIN_MAX_SIZE)
		{
			ft_printf("len[%d]:%x\n", i, (int)line[i]);
			i++;
		}*/
		ft_printf("ret:%d\n", ret);
		if (ret > D_BIN_MAX_SIZE)
			return (-11);
		//if (ft_strlen(line) > (D_BIN_MAX_SIZE + CHAMP_MAX_SIZE) * 8)
		//	return (-11);
		if ((ret = ft_check_header(champ, line, conf)) < 0)
			return (ret);
		if ((ret = ft_check_inst(champ, line)) < 0)
			return (ret);
		ft_print_champ(champ);
		champ = champ->next;
	}
	return (0);
}
