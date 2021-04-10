/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:36:23 by dpowdere          #+#    #+#             */
/*   Updated: 2020/12/19 19:26:38 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>

#include "ft_get_next_line.h"

static size_t	ft_get_line_size(struct s_stash *stash)
{
	struct s_part	*cursor;
	size_t			size;

	if (stash->head->next == NULL)
		return (stash->end - stash->start + 1);
	size = stash->head->size - stash->start;
	cursor = stash->head->next;
	while (cursor && cursor->next)
	{
		size += cursor->size;
		cursor = cursor->next;
	}
	return (size + stash->end + 1);
}

static inline ssize_t	ft_j(struct s_part *cursor, struct s_stash *stash)
{
	ssize_t			j;

	j = 0;
	if (cursor == stash->head)
		j = stash->start;
	return (j);
}

static void	ft_dump_line(struct s_stash *stash, char *line)
{
	struct s_part	*cursor;
	struct s_part	*tmp;
	size_t			i;
	ssize_t			j;

	cursor = stash->head;
	i = 0;
	while (cursor && cursor->next)
	{
		j = ft_j(cursor, stash);
		while (j < cursor->size)
			line[i++] = cursor->s[j++];
		tmp = cursor;
		cursor = cursor->next;
		if (tmp->s)
			free(tmp->s);
		free(tmp);
	}
	j = ft_j(cursor, stash);
	while (j < stash->end)
		line[i++] = stash->tail->s[j++];
	line[i] = '\0';
	stash->head = stash->tail;
	stash->start = stash->end + 1;
	stash->end = DEFAULT_END_POS;
}
