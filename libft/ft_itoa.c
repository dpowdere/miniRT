/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:18:51 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/13 17:49:59 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static inline char	*ft_allocate_string(int n, int *power10, int *sign)
{
	int		digits;
	size_t	size;

	digits = 1;
	*power10 = 1;
	*sign = 1;
	if (n < 0)
		*sign = -1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		*power10 *= 10;
		++digits;
	}
	size = digits + 1;
	if (*sign < 0)
		size += 1;
	return (malloc(size * sizeof(char)));
}

char	*ft_itoa(int n)
{
	char	*s;
	int		power10;
	int		sign;
	int		i;

	s = ft_allocate_string(n, &power10, &sign);
	if (!s)
		return (NULL);
	i = 0;
	if (n < 0)
		s[i++] = '-';
	while (power10 != 0)
	{
		s[i++] = (char)(n / power10 * sign + '0');
		n %= power10;
		power10 /= 10;
	}
	s[i] = '\0';
	return (s);
}
