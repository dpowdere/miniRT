/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:43:15 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/08 22:46:39 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cursor;

	if (!lst)
		return ;
	cursor = *lst;
	while (cursor && cursor->next)
		cursor = cursor->next;
	if (cursor)
		cursor->next = new;
	else
		*lst = new;
}
