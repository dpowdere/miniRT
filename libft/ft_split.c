/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:41:28 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/27 15:03:37 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libft.h"

static int	ft___count_segments(char const *s, char c)
{
	int	n_segments;
	int	i;

	n_segments = 0;
	i = -1;
	while (s && s[++i])
		if ((s[i] == c && s[i + 1] != c) || (i == 0 && s[i] != c))
			++n_segments;
	return (n_segments);
}

static void	ft___free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
}

static char	**ft___populate_array(char **arr, char const *s, char separator)
{
	int		i;
	char	*e;
	char	*p;

	i = -1;
	while (*s)
	{
		if (*s++ == separator)
			continue ;
		e = ft_strchr(--s, separator);
		if (!e)
			p = ft_strdup(s);
		else
			p = ft_substr(s, 0, e - s);
		if (!p)
		{
			ft___free_array(arr);
			return (NULL);
		}
		arr[++i] = p;
		s = e;
	}
	arr[++i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char separator)
{
	char	**arr;
	int		n_segments;

	if (!s)
		return (NULL);
	n_segments = ft___count_segments(s, separator);
	arr = (char **)malloc((n_segments + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (ft___populate_array(arr, s, separator));
}
