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

char	*ft_itoa(int n)
{
	int		i;
	int		digits;
	int		power10;
	char	*s;

	digits = 1;
	power10 = 1;
	i = n;
	while ((i /= 10) != 0)
	{
		power10 *= 10;
		++digits;
	}
	if (!(s = (char *)malloc((digits + (n < 0 ? 2 : 1)) * sizeof(char))))
		return (NULL);
	if (n < 0)
		s[i++] = '-';
	while (power10 != 0)
	{
		s[i++] = (char)(n / power10 * (n < 0 ? -1 : 1) + '0');
		n %= power10;
		power10 /= 10;
	}
	s[i] = '\0';
	return (s);
}
