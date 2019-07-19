/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champion_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:08:47 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/19 12:11:56 by fdagbert         ###   ########.fr       */
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
	champ->init_pc = champ->init_pc * (conf->nb_player - champ->id - 1);
	return (0);
}

int			ft_check_inst(t_champ *champ, char *line)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = D_HEAD_SIZE;
	/*unsigned char	ocp;
	t_ocp			ocp_split;
	ocp = line[j];
	ft_printf("OCP :%b\n", ocp);
	ocp = ocp & 0xFF;
	ocp_split.arg1 = ocp >> 6;
	ocp = ocp & 0x3F;
	ocp_split.arg2 = ocp >> 4;
	ocp = ocp & 0x0F;
	ocp_split.arg3 = ocp >> 2;
	ocp = ocp & 0x03;
	ocp_split.arg4 = ocp;
	ft_printf("OCP SPLIT:%x %x %x %x\n", ocp_split.arg1, ocp_split.arg2, ocp_split.arg3, ocp_split.arg4);*/
	while (i < champ->inst_size)
		champ->inst[i++] = line[j++];
	return (0);
}

static void		ft_print_champ(t_champ *champ)
{
	int		i;

	i = 0;
	ft_printf("champ path:%s, fd:%d, id:%u, nb_live:%u, init_pc:%u, inst_size:%u, magic:%x, pad1:%x, pad2:%x, name:%s, comment:%s\n", champ->path, champ->fd, champ->id, champ->nb_live, champ->init_pc, champ->inst_size, champ->magic, champ->padding1, champ->padding2, champ->name, champ->comment);
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

/*static int		ft_check_base(unsigned char *line)
  {
  ft_printf("len:%d, line:%s\n", ft_strlen((char *)line), line);
  return (0);
  }*/

int				ft_champion_parser(t_champ *champ, t_conf *conf)
{
	int				ret;
	char			line[D_BIN_MAX_SIZE + 1];

	ret = 0;
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
		if (conf->opt[8])
			ft_print_champ(champ);
		champ = champ->next;
	}
	return (0);
}
