#include "asm.h"

int		add_to_queue(t_asm *glob, t_input *input
		, t_label *label, int type)
{
	t_queue		new;
	t_list		*elem;

	new.to_complete = NULL;
	new.node = NULL;
	new.parent = NULL;
	new.size = 0;
	if (!(elem = ft_lstnew(&new, sizeof(t_queue))))
		return (0);
	((t_queue *)elem->content)->node = input;
	((t_queue *)elem->content)->parent = label;
	((t_queue *)elem->content)->to_complete = glob->ptr;
	if ((input->op_index < 8 || input->op_index == 12) && (type & T_DIR))
	{
		glob->ptr += 4;
		((t_queue *)elem->content)->size = 4;
	}
	else
	{
		glob->ptr += 2;
		((t_queue *)elem->content)->size = 2;
	}
	ft_lstprepend(&glob->queue, elem);
	return (1);
}
