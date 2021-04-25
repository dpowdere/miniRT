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

#include <stdio.h>

#include "minirt.h"

t_ray	rt_init_ray(int u, int v, t_camera *camera, t_scene *scene)
{
	t_ray	ray;
	double	x;
	double	y;
	double	z;

	x = u / (double)scene->width * camera->width - camera->width / 2.;
	y = camera->height / 2. - v / (double)scene->height * camera->height;
	z = 1.;
	ray.origin = camera->origin;
	ray.orientation = vt_init(
			camera->x_ornt.x * x + camera->y_ornt.x * y + camera->z_ornt.x * z,
			camera->x_ornt.y * x + camera->y_ornt.y * y + camera->z_ornt.y * z,
			camera->x_ornt.z * x + camera->y_ornt.z * y + camera->z_ornt.z * z);
	return (ray);
}

t_color	rt_trace_ray(int u, int v, t_camera *camera, t_scene *scene)
{
	t_ray	local_ray;
	t_x		xx;
	t_x		nearest_xx;
	t_list	*elem;

	local_ray = rt_init_ray(u, v, camera, scene);
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

void	rt_render_viewport(int serial_number, t_camera *camera, t_scene *scene)
{
	const int	total = scene->width * scene->height;
	int			progress;
	int			u;
	int			v;
	t_color		color;

	progress = 0;
	v = 0;
	while (v < scene->height)
	{
		u = 0;
		while (u < scene->width)
		{
			color = rt_trace_ray(u, v, camera, scene);
			rt_put_pixel(camera->viewport, u, v, rt_color_to_int(color));
			progress = ((u + 1) + (v + 1) * scene->width) * 100 / total;
			printf("\rViewport rendering for camera %i [ %i%% ]" AEC_ERASE_EOL,
				serial_number, progress);
			++u;
		}
		++v;
	}
}

void	rt_render_scene(t_scene *scene)
{
	t_list		*elem;
	t_camera	*camera;
	int			camera_serial_number;

	elem = scene->cameras;
	camera_serial_number = 1;
	printf(AEC_HIDE_CURSOR);
	while (elem)
	{
		camera = (t_camera *)elem->content;
		rt_render_viewport(camera_serial_number++, camera, scene);
		elem = elem->next;
	}
	printf(AEC_ERASE_LINE "\n" AEC_SHOW_CURSOR);
}
