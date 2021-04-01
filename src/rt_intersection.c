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

t_x	rt_get_no_intersection(void *obj)
{
	t_x x;

	x.object = obj;
	x.point = vt_init(INFINITY, INFINITY, INFINITY);
	return (x);
}

t_x	rt_get_nearest_intersection(t_point origin, t_x x1, t_x x2)
{
	const t_point	p1 = x1.point;
	const t_point	p2 = x2.point;

	if (vt_isinf(p1))
		return (x2);
	else if (vt_isinf(p2) || vt_isequal(p1, p2))
		return (x1);
	if (vt_distance(origin, p1) <= vt_distance(origin, p2))
		return (x1);
	return (x2);
}

t_x	rt_get_intersection(t_point origin, t_vector ray, void *object)
{
	const t_otype objtype = (t_objtype)((t_object *)object)->type;

	if (objtype == RT_SPHERE)
		return (rt_sphere_intersection(origin, ray, object));
	return (rt_get_no_intersection(object));
}
