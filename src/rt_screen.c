/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 20:13:15 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/04 21:39:00 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"

t_vector	rt_init_ray_on_plane_non_equal_angles(
				int u, int v, t_camera *camera, t_scene *scene)
{
	double	x;
	double	y;
	double	z;

	x = u / (double)scene->width * camera->width - camera->width / 2.;
	y = camera->height / 2. - v / (double)scene->height * camera->height;
	z = 1.;
	return (vt_init(x, y, z));
}

t_vector	rt_init_ray_on_plane_equal_angles(
				int u, int v, t_camera *camera, t_scene *scene)
{
	double	x;
	double	y;
	double	z;
	double	pix_angle;
	double	angle;

	pix_angle = camera->horizontal_angle / (scene->width - 1);
	angle = (u - (double)scene->width / 2. + 0.5) * pix_angle;
	if (fabs(angle) < EPS)
		x = 0.;
	else
		x = copysign(tan(fabs(angle)), angle);
	pix_angle = camera->vertical_angle / (scene->height - 1);
	angle = (v - (double)scene->height / 2. + 0.5) * pix_angle;
	if (fabs(angle) < EPS)
		y = 0.;
	else
		y = copysign(tan(fabs(angle)), -angle);
	z = 1.;
	return (vt_init(x, y, z));
}

t_vector	rt_init_ray_on_sphere(int u, int v, t_camera *c)
{
	const double	h_angle = c->pixel_size * u - c->horizontal_angle / 2;
	const double	v_angle = c->pixel_size * v - c->vertical_angle / 2;
	t_vector		vec;

	vec = vt_init(
			sin(h_angle) * cos(v_angle),
			-sin(v_angle),
			cos(h_angle) * cos(v_angle));
	return (vec);
}

t_vector	rt_init_ray_on_cylinder(int u, int v, t_camera *c)
{
	const double	h_angle = c->pixel_size * u - c->horizontal_angle / 2;
	const double	v_angle = c->pixel_size * v - c->vertical_angle / 2;

	return (vt_init(sin(h_angle), -v_angle, cos(h_angle)));
}
