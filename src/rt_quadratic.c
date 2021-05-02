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
	double	magic;

	roots.discriminant = b * b - 4 * a * c;
	roots.root1 = NAN;
	roots.root2 = NAN;
	a2 = a * 2;
	if (fabs(roots.discriminant) < EPS)
		roots.root1 = -b / a2;
	else if (roots.discriminant >= EPS)
	{
		dsqrt = sqrt(roots.discriminant);
		if (b > 0)
			magic = -1 * (b + dsqrt) / 2;
		else
			magic = -1 * (b - dsqrt) / 2;
		roots.root1 = magic / a;
		roots.root2 = c / magic;
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
