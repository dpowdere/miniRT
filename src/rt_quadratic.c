/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_quadratic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 22:34:36 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/01 22:34:53 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"

#define T_LIMIT	0.0

t_roots	rt_quadratic_equation(t_float a, t_float b, t_float c)
{
	t_roots	roots;
	t_float	a2;
	t_float	dsqrt;

	roots.discriminant = b * b - 4 * a * c;
	roots.root1 = NAN;
	roots.root2 = NAN;
	if (roots.discriminant >= 0.)
	{
		a2 = a * 2;
		dsqrt = SQRT(roots.discriminant);
		roots.root1 = (-b + dsqrt) / a2;
		if (roots.discriminant > 0.)
			roots.root2 = (-b - dsqrt) / a2;
	}
	return (roots);
}

t_float	rt_get_quadratic_root(t_roots r, int *is_inside)
{
	*is_inside = FALSE;
	if (r.discriminant == 0. && r.root1 > T_LIMIT)
		return (r.root1);
	if (r.discriminant > 0.)
	{
		if (r.root1 > T_LIMIT && r.root2 <= T_LIMIT)
		{
			*is_inside = TRUE;
			return (r.root1);
		}
		if (r.root2 > T_LIMIT)
			return (r.root2);
	}
	return (NAN);
}
