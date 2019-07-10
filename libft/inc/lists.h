/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 22:16:55 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/03 14:39:33 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstprepend(t_list **alst, t_list *new);
void				ft_lstappend(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstclr(t_list *alst);
void				ft_lst_mergesort(t_list **source,
					int (*cmp)(void *, void *));
t_list				*ft_lst_bubblesort(t_list *lst, int (*cmp)(void *, void *));
void				ft_lstrev(t_list **alst);
int					ft_islist_sorted(t_list *alst,
					int size, int (*cmp)(void *, void *));
t_list				*ft_lstswap(t_list *a, t_list *b);
void				ft_lstpush(t_list **src, t_list **dest);
void				ft_lstrotate(t_list **alst);
void				ft_lstrevrotate(t_list **alst);
int					ft_lstcount(t_list *lst);
t_list				*ft_lstcpy(t_list *source, int (*cpy)(void *, void *));
t_list				*ft_lstncpy(t_list *source,
					int size, int (*cpy)(void *, void *));
void				ft_lstpop(t_list **lst, t_list *target
					, void (*f)(void *, size_t));

#endif
