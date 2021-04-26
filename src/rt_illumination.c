#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "minirt.h"

t_color	rt_ambient_illumination_only(t_x x, t_scene *scene)
{
	const t_sphere	*sp = x.object;
	double			angle;
	double			factor;
	t_color			color;

	if (sp == NULL || vt_isinf(x.point))
		return (rt_init_color(0, 0, 0));
	angle = vt_angle(x.normal, x.ray.orientation);
	factor = (angle - acos(0)) / acos(0);
	if (x.is_flip_side)
		factor = 1. - factor;
	factor *= scene->ambient;
	color = rt_color_merge(sp->color, scene->ambient_color);
	color = rt_color_brightness(color, factor);
	return (color);
}

t_color	rt_get_point_illumination(t_x x, t_light *light)
{
	const t_vector	light_source = vt_add(light->origin, vt_inv(x.point));
	double			angle;
	double			factor;
	t_color			color;

	angle = vt_angle(x.normal, light_source);
	if (acos(0) - angle < EPS)
	{
		dprintf(2, " color + [angle: %g, f: %g, (0, 0, 0)]", angle, 1. - angle / acos(0));
		return (rt_init_color(0, 0, 0));
	}
	if (angle < EPS)
		angle = 0.;
	factor = 1. - angle / acos(0);
	factor *= light->intensity;
	color = rt_color_merge(x.color, light->color);
	color = rt_color_brightness(color, factor);
	dprintf(2, " color + [(%i, %i, %i)", x.color.red, x.color.green, x.color.blue);
	dprintf(2, " * (%i, %i, %i)", light->color.red, light->color.green, light->color.blue);
	dprintf(2, " * (angle: %g, f:%g * intty:%g = %g)", angle, 1. - angle / acos(0), light->intensity, factor);
	dprintf(2, " = (%i, %i, %i)]", color.red, color.green, color.blue);
	return (color);
}
