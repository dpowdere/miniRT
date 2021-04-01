/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:20:16 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/24 16:21:36 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>

#include "minirt.h"

t_color	rt_trace_ray(int u, int v, t_camera *camera, t_scene *scene)
{
	t_vector	local_ray;
	t_x			intersection;
	t_x			nearest_intersection;
	t_list		*elem;

	local_ray = vt_init(scene->width / 2.0 + u, scene->height / 2.0 - v, 1.0);
	nearest_intersection = rt_get_no_intersection(NULL);
	elem = scene->objects;
	while (elem)
	{
		intersection = rt_get_intersection(
				camera->location, local_ray, elem->content);
		nearest_intersection = rt_get_nearest_intersection(
				camera->location, nearest_intersection, intersection);
		elem = elem->next;
	}
	return (rt_get_color(nearest_intersection));
}

void	rt_render_viewport(t_camera *camera, t_scene *scene)
{
	int		u;
	int		v;
	t_color	color;

	v = 0;
	while (v < scene->height)
	{
		u = 0;
		while (u < scene->width)
		{
			color = rt_trace_ray(u, v, camera, scene);
			rt_put_pixel(camera->viewport, u, v, rt_color_to_int(color));
			++u;
		}
		++v;
	}
}

void	rt_render_scene(t_scene *scene)
{
	t_list		*elem;
	t_camera	*camera;

	elem = scene->cameras;
	while (elem)
	{
		camera = (t_camera *)elem->content;
		rt_render_viewport(camera, scene);
		elem = elem->next;
	}
}
