/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 04:00:52 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/25 04:01:22 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"

int	vt_isinf(t_vector v)
{
	return (isinf(v.x) || isinf(v.y) || isinf(v.z));
}

int	vt_isequal(t_vector a, t_vector b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

/*
** Geometric projection of a vector onto another vector
*/
t_vector	vt_proj_geom(t_vector a, t_vector b)
{
	t_scalar	oriented_length;

	oriented_length = vt_mul_dot(a, b) / vt_magnitude(b);
	return (vt_mul_sc(vt_normalize(b), oriented_length));
}

/*
** Algebraic projection (oriented length) of a vector onto another vector
*/
t_scalar	vt_proj_alg(t_vector a, t_vector b)
{
	t_scalar	oriented_length;

	oriented_length = vt_mul_dot(a, b) / vt_magnitude(b);
	return (oriented_length);
}

/*
** Convert degrees to radians
*/
double	vt_rad(double deg)
{
	return (deg / 180. * acos(-1.));
}
