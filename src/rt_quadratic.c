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

t_roots	rt_quadratic_equation(double a, double b, double c)
{
	t_roots	roots;
	double	a2;
	double	dsqrt;

	roots.discriminant = b * b - 4 * a * c;
	roots.root1 = NAN;
	roots.root2 = NAN;
	if (roots.discriminant > -EPS)
	{
		a2 = a * 2;
		dsqrt = sqrt(roots.discriminant);
		roots.root1 = (-b + dsqrt) / a2;
		if (roots.discriminant >= EPS)
			roots.root2 = (-b - dsqrt) / a2;
	}
	return (roots);
}

double	rt_get_quadratic_root(t_roots r, int *is_inside, double limit)
{
	*is_inside = FALSE;
	if (fabs(r.discriminant) < EPS && r.root1 >= EPS && r.root1 < limit)
		return (r.root1);
	if (r.discriminant >= EPS)
	{
		if (r.root1 >= EPS && r.root1 < limit && r.root2 < EPS)
		{
			*is_inside = TRUE;
			return (r.root1);
		}
		if (r.root2 >= EPS && r.root2 < limit)
			return (r.root2);
	}
	return (NAN);
}
