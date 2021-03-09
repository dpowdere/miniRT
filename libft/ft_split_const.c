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

#define IN_SEGMENT		1
#define IN_SEPARATOR	0

static void	ft___count(char const *s, char c,
					size_t *n_segments, size_t *n_chars)
{
	int		where;

	*n_segments = 0;
	*n_chars = 0;
	where = IN_SEPARATOR;
	while (*s)
	{
		if (*s == c && where == IN_SEGMENT)
			where = IN_SEPARATOR;
		else if (*s != c)
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

static void	ft___fill(char const *s, char c, char **mem, size_t n_segments)
{
	char	*write_cursor;
	int		where;

	*(mem + n_segments) = NULL;
	write_cursor = (char *)(mem + n_segments + 1);
	where = IN_SEPARATOR;
	while (s && *s)
	{
		if (*s == c && where == IN_SEGMENT)
		{
			where = IN_SEPARATOR;
			*write_cursor++ = '\0';
		}
		else if (*s != c && where == IN_SEGMENT)
			*write_cursor++ = *s;
		else if (*s != c && where == IN_SEPARATOR)
		{
			where = IN_SEGMENT;
			*write_cursor = *s;
			*mem++ = write_cursor++;
		}
		++s;
	}
}

char *const	*ft_split_const(char const *s, char c)
{
	size_t	n_segments;
	size_t	n_chars;
	size_t	size;
	char	**string_array;

	n_segments = 0;
	n_chars = 0;
	if (s)
		ft___count(s, c, &n_segments, &n_chars);
	size = (n_segments + 1) * sizeof(char *)
			+ (n_chars + n_segments) * sizeof(char);
	string_array = (char **)malloc(size);
	if (!string_array)
		return (NULL);
	while (size > 0)
		((char *)string_array)[--size] = '\0';
	ft___fill(s, c, string_array, n_segments);
	return ((char *const *)string_array);
}
