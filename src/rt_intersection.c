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
	x.normal = vt_init(0, 0, 0);
	x.is_flip_side = FALSE;
	x.color = rt_init_color(0, 0, 0);
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

t_x	rt_get_intersection(t_ray ray, void *object, double limit)
{
	const t_otype	objtype = (t_objtype)((t_object *)object)->type;

	if (objtype == RT_SPHERE)
		return (rt_sphere_intersection(ray, object, limit));
	else if (objtype == RT_PLANE)
		return (rt_plane_intersection(ray, object, limit));
	return (rt_get_no_intersection(ray, object));
}

t_color	rt_get_illumination(t_x x, t_scene *scene)
{
	t_list	*elem;
	t_light	*light;
	t_color color;

	elem = scene->lights;
	color = rt_color_merge(x.color, scene->ambient_color);
	color = rt_color_brightness(color, scene->ambient);
	while (elem)
	{
		light = (t_light *)elem->content;
		color = rt_color_add(color, rt_get_point_illumination(x, light));
		elem = elem->next;
	}
	return (color);
}

t_color	rt_get_color(t_x intersection, t_scene *scene)
{
	t_otype		objtype;

	if (intersection.object == NULL || vt_isinf(intersection.point))
		return (rt_init_color(0, 0, 0));
	objtype = (t_objtype)((t_object *)intersection.object)->type;
	if (objtype == RT_SPHERE)
		rt_sphere_normal(&intersection);
	else if (objtype == RT_PLANE)
		rt_plane_normal(&intersection);
	else
		return (rt_init_color(0, 0, 0));
	return (rt_get_illumination(intersection, scene));
}
