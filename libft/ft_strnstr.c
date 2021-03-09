/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 08:36:28 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/04 09:32:00 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	is_match;
	size_t	needle_len;
	size_t	i;
	size_t	j;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	i = 0;
	while (i + needle_len < len + 1 && haystack[i])
	{
		is_match = 1;
		j = 0;
		while (is_match && i + j < len && j < needle_len && needle[j])
		{
			if (haystack[i + j] != needle[j])
				is_match = 0;
			++j;
		}
		if (is_match)
			return ((char *)haystack + i);
		++i;
	}
	return (NULL);
}
