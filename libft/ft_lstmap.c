/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:34:19 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/22 20:12:21 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *mapped_lst;
	t_list *list_node;

	if (!lst || !f || !del)
		return (NULL);
	mapped_lst = NULL;
	while (lst)
	{
		list_node = ft_lstnew((*f)(lst->content));
		if (!list_node)
		{
			if (mapped_lst)
				ft_lstclear(&mapped_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&mapped_lst, list_node);
		lst = lst->next;
	}
	return (mapped_lst);
}
