/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:56:50 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/25 11:29:21 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substring;
	size_t			len2;

	if (!s)
		return (NULL);
	len2 = ft_strlen(s);
	if (len2 > start)
		len2 = len2 - start;
	else
		len2 = 0;
	if (len2 > len)
		len2 = len;
	substring = (char *)malloc((len2 + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = start;
	while (i - start < len2 && s[i])
	{
		substring[i - start] = s[i];
		++i;
	}
	substring[i - start] = '\0';
	return (substring);
}
