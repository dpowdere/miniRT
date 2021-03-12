/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:46:31 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 03:02:46 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Naive and lazy conversion of string to int, partly similar
** to `strtoi` BSD function and `strtol`, `strtoll`, `strtoq`
** stdlib functions; returns no error.
*/

#define DIGITS		"0123456789abcdefghijklmnopqrstuvwxyz"
#define DIGITS_N	36

int	ft_strtoi(const char *nptr, char **endptr, int base)
{
	int index;
	int sign;
	int n;

	sign = 1;
	n = 0;
	if (base < 1 || base > DIGITS_N)
		return (n);
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n' || *nptr == '\r'
			|| *nptr == '\t' || *nptr == '\v')
		++nptr;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		++nptr;
	}
	--nptr;
	while ((index = ft_str_index(DIGITS, *++nptr)) >= 0 && index < base)
		n = n * base + index * sign;
	if (endptr != NULL)
		*endptr = (char *)nptr;
	return (n);
}
