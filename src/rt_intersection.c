/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:33:31 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/31 19:33:33 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>

#include "minirt.h"

t_x	rt_get_no_intersection(t_ray ray, void *obj)
{
	t_x	x;

	x.object = obj;
	x.ray = ray;
	x.point = vt_init(INFINITY, INFINITY, INFINITY);
	x.is_flip_side = FALSE;
	return (x);
}

t_x	rt_get_nearest_intersection(t_x x1, t_x x2)
{
	const t_point	origin = x1.ray.origin;
	const t_point	p1 = x1.point;
	const t_point	p2 = x2.point;
	const int		no_object1 = x1.object == NULL;
	const int		no_object2 = x2.object == NULL;

	if (no_object1 || vt_isinf(p1))
		return (x2);
	else if (no_object2 || vt_isinf(p2) || vt_isequal(p1, p2))
		return (x1);
	if (vt_distance(origin, p1) <= vt_distance(origin, p2))
		return (x1);
	return (x2);
}

t_x	rt_get_intersection(t_ray ray, void *object)
{
	const t_otype	objtype = (t_objtype)((t_object *)object)->type;

	if (objtype == RT_SPHERE)
		return (rt_sphere_intersection(ray, object));
	return (rt_get_no_intersection(ray, object));
}
