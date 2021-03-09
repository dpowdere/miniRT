/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 09:04:55 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/24 20:56:13 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	if (n == 0)
		return (0);
	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (i + 1 < n && a[i] && b[i] && a[i] == b[i])
		++i;
	return ((int)(a[i] - b[i]));
}
