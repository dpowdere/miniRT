/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:33:00 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/26 16:21:52 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = 0;
	src_len = 0;
	if (dst)
		dst_len = ft_strlen(dst);
	if (src)
		src_len = ft_strlen(src);
	if (size > 0 && dst_len < size)
	{
		i = dst_len;
		j = 0;
		while (i < size - 1 && j < src_len)
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	if (dst_len > size)
		return (size + src_len);
	return (dst_len + src_len);
}
