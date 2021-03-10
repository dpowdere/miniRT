/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 01:14:57 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/11 01:15:05 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static inline void	ft__calc_sign(const char **ptr, int *sign)
{
	*sign = (**ptr == '-' ? -1 : +1);
	++*ptr;
}

static inline void	ft__calc_frac(const char **ptr, int *frac, double *n)
{
	++*ptr;
	while (**ptr >= '0' && **ptr <= '9')
	{
		++*frac;
		*n = *n * 10 + (*(*ptr)++ - '0');
	}
}

static inline void	ft__calc_exp(const char **ptr, int *exp, int *exp_sign)
{
	++*ptr;
	if (**ptr == '+' || **ptr == '-')
		ft__calc_sign(ptr, exp_sign);
	while (**ptr >= '0' && **ptr <= '9')
		*exp = *exp * 10 + (*(*ptr)++ - '0');
	*exp *= *exp_sign;
}

static inline void	ft__calc_final_n(double *n, int frac, int exp)
{
	int floating_point_shift;

	floating_point_shift = exp - frac;
	while (floating_point_shift != 0)
	{
		if (floating_point_shift < 0)
		{
			*n /= 10;
			++floating_point_shift;
		}
		else
		{
			*n *= 10;
			--floating_point_shift;
		}
	}
}

/*
** A naive imprecise implementation of `strtod` function
** without check if the correct value would cause overflow
** or underflow and without much care of roundoff errors.
*/

double				ft_strtod(const char *nptr, char **endptr)
{
	double	n;
	int		frac;
	int		exp;
	int		sign;
	int		exp_sign;

	n = +0.0;
	frac = 0;
	exp = 0;
	sign = 1;
	exp_sign = 1;
	if (*nptr == '+' || *nptr == '-')
		ft__calc_sign(&nptr, &sign);
	while (*nptr >= '0' && *nptr <= '9')
		n = n * 10 + (*nptr++ - '0');
	if (*nptr == '.')
		ft__calc_frac(&nptr, &frac, &n);
	if (*nptr == 'e' || *nptr == 'E')
		ft__calc_exp(&nptr, &exp, &exp_sign);
	ft__calc_final_n(&n, frac, exp);
	if (endptr != NULL)
		*endptr = (char *)nptr;
	return (n);
}
