/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_const.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:41:28 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/27 12:22:58 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** `ft_split_const` allocates a single contiguous array of memory blocks and
** populates them both with an array of pointers to splitted C-strings and
** with the strings themselves. So when deallocation is needed, you only have
** to deallocate the whole range at once without hassle of deallocating the
** individual strings.
*/
#include <stddef.h>
#include <stdlib.h>

#include "libft.h"

#define IN_SEGMENT		1
#define IN_SEPARATOR	0

static void	ft___count(const char *s, const char *separator_chars,
					size_t *n_segments, size_t *n_chars)
{
	int		where;
	int		is_sep_char;

	*n_segments = 0;
	*n_chars = 0;
	where = IN_SEPARATOR;
	while (*s)
	{
		is_sep_char = !!ft_strchr(separator_chars, *s);
		if (is_sep_char && where == IN_SEGMENT)
			where = IN_SEPARATOR;
		else if (!is_sep_char)
		{
			++*n_chars;
			if (where == IN_SEPARATOR)
			{
				where = IN_SEGMENT;
				++*n_segments;
			}
		}
		++s;
	}
}

static void	ft___fill(const char *s, const char *separator_chars,
						char **mem, size_t n_segments)
{
	char	*write_cursor;
	int		where;
	int		is_sep_char;

	*(mem + n_segments) = NULL;
	write_cursor = (char *)(mem + n_segments + 1);
	where = IN_SEPARATOR;
	while (s && *s)
	{
		is_sep_char = !!ft_strchr(separator_chars, *s);
		if (is_sep_char && where == IN_SEGMENT)
		{
			where = IN_SEPARATOR;
			*write_cursor++ = '\0';
		}
		else if (!is_sep_char && where == IN_SEGMENT)
			*write_cursor++ = *s;
		else if (!is_sep_char && where == IN_SEPARATOR)
		{
			where = IN_SEGMENT;
			*write_cursor = *s;
			*mem++ = write_cursor++;
		}
		++s;
	}
}

char *const	*ft_split_const(const char *s, const char *separator_chars)
{
	size_t	n_segments;
	size_t	n_chars;
	size_t	size;
	char	**string_array;

	n_segments = 0;
	n_chars = 0;
	if (s)
		ft___count(s, separator_chars, &n_segments, &n_chars);
	size = (n_segments + 1) * sizeof(char *)
			+ (n_chars + n_segments) * sizeof(char);
	string_array = (char **)malloc(size);
	if (!string_array)
		return (NULL);
	while (size > 0)
		((char *)string_array)[--size] = '\0';
	ft___fill(s, separator_chars, string_array, n_segments);
	return ((char *const *)string_array);
}
