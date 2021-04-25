/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:44:50 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/02 17:55:18 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>

#include "minirt.h"

static inline int	rt_color_normalize(int x)
{
	if (x < 0)
		x = 0;
	else if (x > 255)
		x = 255;
	return (x);
}

int32_t	rt_color_channels_to_int(int red, int green, int blue)
{
	uint32_t	color;

	color = 0u;
	color |= rt_color_normalize(red) << 16;
	color |= rt_color_normalize(green) << 8;
	color |= rt_color_normalize(blue);
	return (*(int32_t *)&color);
}

int32_t	rt_color_to_int(t_color c)
{
	return (rt_color_channels_to_int(c.red, c.green, c.blue));
}

t_color	rt_init_color(int red, int green, int blue)
{
	t_color	c;

	c.red = rt_color_normalize(red);
	c.green = rt_color_normalize(green);
	c.blue = rt_color_normalize(blue);
	return (c);
}

t_color	rt_get_ambient_color(t_vector normal, t_x x, t_scene *scene)
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
