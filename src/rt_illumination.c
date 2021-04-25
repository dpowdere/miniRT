#include <math.h>
#include <stddef.h>

#include "minirt.h"

t_color	rt_get_ambient_illumination(t_vector normal, t_x x, t_scene *scene)
{
	const t_sphere	*sp = x.object;
	double			angle;
	double			factor;
	t_color			color;

	if (sp != NULL && !vt_isinf(x.point))
	{
		angle = vt_angle(normal, x.ray.orientation);
		factor = (angle - acos(0)) / acos(0);
		if (x.is_flip_side)
			factor = 1. - factor;
		factor *= scene->ambient;
		color = rt_init_color(
				(sp->color.red + scene->ambient_color.red) * factor,
				(sp->color.green + scene->ambient_color.green) * factor,
				(sp->color.blue + scene->ambient_color.blue) * factor);
		return (color);
	}
	return (rt_init_color(0, 0, 0));
}

t_color	rt_get_point_illumination(
			t_color point_color, t_vector point_origin, t_vector point_normal,
			t_light *light)
{
	const t_vector	light_source = vt_add(light->origin, vt_inv(point_origin));
	double			angle;
	double			factor;
	t_color			color;

	angle = vt_angle(point_normal, light_source);
	if (acos(0) - angle < EPS)
		return (point_color);
	factor = 1. - angle / acos(0);
	factor *= light->intensity;
	color = rt_init_color(
			(point_color.red + light->color.red) * factor,
			(point_color.green + light->color.green) * factor,
			(point_color.blue + light->color.blue) * factor);
	return (color);
}
