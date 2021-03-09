/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:21:26 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/21 22:21:44 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cursor;
	t_list	*empty_element;

	if (!lst || !del)
		return ;
	cursor = *lst;
	while (cursor)
	{
		(*del)(cursor->content);
		empty_element = cursor;
		cursor = cursor->next;
		empty_element->next = NULL;
		free(empty_element);
	}
	*lst = NULL;
}
