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
#include <stdio.h>

#include "minirt.h"

t_color	rt_trace_ray(int u, int v, t_camera *camera, t_scene *scene)
{
	t_ray	local_ray;
	t_x		xx;
	t_x		nearest_xx;
	t_list	*elem;

	local_ray.origin = camera->origin;
	local_ray.orientation = vt_normalize(vt_init(
			u / (t_float)scene->width * camera->width - camera->width / 2.0,
			camera->height / 2.0 - v / (t_float)scene->height * camera->height,
			1.0));
	nearest_xx = rt_get_no_intersection(local_ray, NULL);
	elem = scene->objects;
	while (elem)
	{
		xx = rt_get_intersection(local_ray, elem->content);
		nearest_xx = rt_get_nearest_intersection(nearest_xx, xx);
		elem = elem->next;
	}
	return (rt_get_color(nearest_xx, scene));
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
