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
