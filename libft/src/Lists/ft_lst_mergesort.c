/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mergesort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:02:58 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/30 11:06:10 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*merge_lists(t_list *a, t_list *b, int (*cmp)(void *, void *))
{
	t_list		*merged_list;

	merged_list = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (cmp(a->content, b->content) <= 0)
	{
		merged_list = a;
		merged_list->next = merge_lists(a->next, b, cmp);
	}
	else
	{
		merged_list = b;
		merged_list->next = merge_lists(a, b->next, cmp);
	}
	return (merged_list);
}

static void		partition(t_list *head, t_list **front, t_list **back)
{
	t_list		*fast;
	t_list		*slow;

	if (head == NULL || head->next == NULL)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

void			ft_lst_mergesort(t_list **source, int (*cmp)(void *, void *))
{
	t_list		*head;
	t_list		*a;
	t_list		*b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	partition(head, &a, &b);
	ft_lst_mergesort(&a, cmp);
	ft_lst_mergesort(&b, cmp);
	*source = merge_lists(a, b, cmp);
}
