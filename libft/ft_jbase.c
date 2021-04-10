/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_base.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:50:09 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/04 16:53:07 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define LOWER_DIGITS "0123456789abcdefghijklmnopqrstuvwxyz"
#define UPPER_DIGITS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

static inline char	*ft_ji_allocate_string(
						intmax_t n, intmax_t *power, int *sign, int base)
{
	intmax_t	i;
	size_t		size;
	int			n_digits;
	char		*s;

	n_digits = 1;
	*power = 1;
	i = n / base;
	while (i != 0)
	{
		i /= base;
		*power *= base;
		++n_digits;
	}
	size = n_digits + 1;
	*sign = 1;
	if (n < 0)
	{
		*sign = -1;
		size += 1;
	}
	s = malloc(size * sizeof(char));
	return (s);
}

static inline char	*ft_ju_allocate_string(
						uintmax_t n, uintmax_t *power, int base)
{
	uintmax_t	i;
	int			n_digits;
	char		*s;

	n_digits = 1;
	*power = 1;
	i = n / base;
	while (i != 0)
	{
		i /= base;
		*power *= base;
		++n_digits;
	}
	s = malloc(n_digits + 1);
	return (s);
}

char	*ft_ji_base(intmax_t n, int base, int use_upper_case)
{
	intmax_t	power;
	intmax_t	i;
	int			sign;
	char		*digits;
	char		*s;

	s = ft_ji_allocate_string(n, &power, &sign, base);
	if (s == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
		s[i++] = '-';
	digits = LOWER_DIGITS;
	if (use_upper_case)
		digits = UPPER_DIGITS;
	while (power != 0)
	{
		s[i++] = *((char *)digits + (n / power * sign));
		n %= power;
		power /= base;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_ju_base(uintmax_t n, int base, int use_upper_case)
{
	uintmax_t	power;
	uintmax_t	i;
	char		*digits;
	char		*s;

	s = ft_ju_allocate_string(n, &power, base);
	if (s == NULL)
		return (NULL);
	i = 0;
	digits = LOWER_DIGITS;
	if (use_upper_case)
		digits = UPPER_DIGITS;
	while (power != 0)
	{
		s[i++] = *((char *)digits + (n / power));
		n %= power;
		power /= base;
	}
	s[i] = '\0';
	return (s);
}
