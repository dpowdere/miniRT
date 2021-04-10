/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:49:51 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/24 21:51:20 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libft.h"

static inline void	ft_find_limits(char const **start, char const **end,
						char const *set)
{
	size_t		set_len;

	set_len = 0;
	if (set)
		set_len = ft_strlen(set);
	while (**start && set_len && ft_strchr(set, **start))
		++*start;
	*end = *start;
	while (**end && *(*end + 1))
		++*end;
	while (*end > *start && set_len && ft_strchr(set, **end))
		--*end;
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t		size;
	char const	*end;
	char		*trimmed;

	if (!str)
		return (NULL);
	ft_find_limits(&str, &end, set);
	size = end - str + 2;
	if (!*str)
		size = 1;
	trimmed = (char *)malloc(size * sizeof(char));
	if (!trimmed)
		return (NULL);
	++end;
	if (*str)
		*(end - str + trimmed) = '\0';
	while (--end >= str)
		*(end - str + trimmed) = *end;
	return (trimmed);
}
