/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 20:13:15 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/04 20:13:48 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"

t_vector	rt_init_ray_on_plane(int u, int v, t_camera *camera, t_scene *scene)
{
    t_vector    vec;

    vec.x = u / (double)scene->width * camera->width - camera->width / 2.;
    vec.y = camera->height / 2. - v / (double)scene->height * camera->height;
    vec.z = 1.;
    return (vec);
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