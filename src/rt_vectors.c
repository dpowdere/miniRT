/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:33:04 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/31 19:33:06 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"

t_vector	vt_init(t_float x, t_float y, t_float z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_scalar	vt_magnitude(t_vector v)
{
	return ((t_scalar)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vt_normalize(t_vector v)
{
	const t_scalar magnitude = vt_magnitude(v);

	v.x /= magnitude;
	v.y /= magnitude;
	v.z /= magnitude;
	return (v);
}

int			vt_isinf(t_vector v)
{
	return (isinf(v.x) || isinf(v.y) || isinf(v.z));
}

int			vt_isequal(t_vector a, t_vector b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

t_scalar	vt_distance(t_point p1, t_point p2)
{
	const t_scalar	dx = p2.x - p1.x;
	const t_scalar	dy = p2.y - p1.y;
	const t_scalar	dz = p2.z - p1.z;

	return ((t_scalar)sqrt(dx * dx + dy * dy + dz * dz));
}

t_vector	vt_add(t_vector a, t_vector b)
{
	t_vector c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vector	vt_inv(t_vector v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_vector	vt_mul_sc(t_vector v, t_scalar k)
{
	v.x = k * v.x;
	v.y = k * v.y;
	v.z = k * v.z;
	return (v);
}

t_scalar	vt_mul_dot(t_vector v, t_vector w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_vector	vt_mul_cross(t_vector v, t_vector w)
{
	t_vector r;

	r.x = v.y * w.z - v.z * w.y;
	r.y = v.z * w.x - v.x * w.z;
	r.z = v.x * w.y - v.y * w.x;
	return (r);
}

t_scalar	vt_angle(t_vector v, t_vector w)
{
	t_scalar	x;

	x = vt_mul_dot(v, w) / (vt_magnitude(v) * vt_magnitude(w));
	return (ACOS(x));
}

/*
** Convert degrees to radians
*/

t_float		vt_rad(t_float deg)
{
	return (deg / 180 * PI);
}
