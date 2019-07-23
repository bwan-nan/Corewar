#include "asm.h"

static t_list	*get_insertion_node(t_list *list)
{
	t_list		*node;
	t_input		*input;

	node = list;
	while (node)
	{
		input = ((t_input *)node->content);
		if (input->type == 'N')
			return (node);
		node = node->next;
	}
	return (NULL);
}

static void 	list_insert(t_list **head, t_list *insertion_node)
{
	t_list *elem;
	t_list *insertion_node_next;

	elem = *head;
	insertion_node_next = insertion_node->next;
	*head = (*head)->next;
	insertion_node->next = elem;
	elem->next = insertion_node_next;
}

static void 	shift_comment(t_list **head, t_list *insertion_node)
{
	t_input		*input;

	input = ((t_input *)(*head)->content);
	if (input->type == 'c' || input->type == 'C')
	{
		list_insert(head, insertion_node);
		shift_comment(head, insertion_node->next);
	}
}

void			reorder_list(t_list **list)
{
	t_list	*node;
	t_input	*input;

	node = *list;
	while (node)
	{
		input = ((t_input *)node->content);
		if (ft_strchr("cCnN", input->type))
			break ;
		node = node->next;
	}
	if (ft_strchr("cC", input->type))
		shift_comment(list, get_insertion_node(*list));
}
