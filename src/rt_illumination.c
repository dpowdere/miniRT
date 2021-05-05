/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_illumination.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:13:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/04 23:08:13 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Light distribution
**
**   https://www.pbr-book.org/3ed-2018/Introduction/
**   Photorealistic_Rendering_and_the_Ray-Tracing_Algorithm#LightDistribution
**
** The differential irradiance, the differential power per area:
**
**   $ \fraq{I \cos\theta}{4\pi r^2} $
**
** The cosine falloff of light (of power $I$) for tilted surfaces, and the
** one-over-$r$-squared falloff of light with distance.
*/

#define POWER_COEF	0.5

t_color	rt_get_point_illumination(t_x x, t_light *light)
{
	const t_vector	light_source = vt_add(light->origin, vt_inv(x.point));
	double			factor;
	t_scalar		distance_from_light;
	t_color			color;

	factor = vt_cos_angle(x.normal, light_source);
	if (factor < EPS)
		return (rt_init_color(0, 0, 0));
	factor *= light->intensity;
	if (!RT_CONFIG_NO_LIGHT_ATTENUATION)
	{
		distance_from_light = vt_magnitude(light_source) * POWER_COEF;
		factor /= distance_from_light * distance_from_light;
	}
	color = rt_color_merge(x.color, light->color);
	color = rt_color_brightness(color, factor);
	return (color);
}

int	rt_is_point_shaded(t_x x, t_light *light, t_scene *scene)
{
	t_list	*elem;
	t_ray	shadow_ray;
	t_x		shadow_x;

	elem = scene->objects;
	shadow_ray.origin = vt_add(x.point, vt_mul_sc(x.normal, 1e-5));
	shadow_ray.orientation = vt_add(light->origin, vt_inv(shadow_ray.origin));
	if (vt_cos_angle(x.normal, shadow_ray.orientation) < EPS)
		return (TRUE);
	while (elem)
	{
		if (elem->content == x.object)
		{
			elem = elem->next;
			continue ;
		}
		shadow_x = rt_get_intersection(shadow_ray, elem->content, 1.);
		if (!vt_isinf(shadow_x.point))
			return (TRUE);
		elem = elem->next;
	}
	return (FALSE);
}

t_color	rt_get_illumination(t_x x, t_scene *scene)
{
	t_list	*elem;
	t_light	*light;
	t_color	color;
	int		is_not_shaded;

	elem = scene->lights;
	color = rt_color_merge(x.color, scene->ambient_color);
	color = rt_color_brightness(color, scene->ambient);
	while (elem)
	{
		light = (t_light *)elem->content;
		is_not_shaded = !rt_is_point_shaded(x, light, scene);
		if (is_not_shaded)
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
	if (objtype == RT_CYLINDER)
		rt_cylinder_normal(&intersection);
	else if (objtype == RT_PLANE)
		rt_plane_normal(&intersection);
	else if (objtype == RT_SPHERE)
		rt_sphere_normal(&intersection);
	else if (objtype == RT_SQUARE)
		rt_square_normal(&intersection);
	else if (objtype == RT_TRIANGLE)
		rt_triangle_normal(&intersection);
	else
		return (rt_init_color(0, 0, 0));
	return (rt_get_illumination(intersection, scene));
}
