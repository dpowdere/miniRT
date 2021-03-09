/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:44:07 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/04 22:55:58 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;
	size_t			i;

	destination = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (destination < source)
	{
		i = 0;
		while (i < n)
		{
			destination[i] = source[i];
			++i;
		}
	}
	else if (destination > source)
	{
		i = n;
		while (i > 0)
		{
			destination[i - 1] = source[i - 1];
			--i;
		}
	}
	return (dst);
}
