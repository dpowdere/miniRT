#include "minirt.h"

t_color	rt_get_point_illumination(t_x x, t_light *light)
{
	const t_vector	light_source = vt_add(light->origin, vt_inv(x.point));
	double			factor;
	t_color			color;

	factor = vt_cos_angle(x.normal, light_source);
	if (factor < EPS)
		return (rt_init_color(0, 0, 0));
	factor *= light->intensity;
	color = rt_color_merge(x.color, light->color);
	color = rt_color_brightness(color, factor);
	return (color);
}
