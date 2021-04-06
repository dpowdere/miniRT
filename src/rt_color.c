/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:44:50 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/02 17:55:18 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "minirt.h"

static inline int	rt_normalize(int x)
{
	if (x < 0)
		x = 0;
	else if (x > 255)
		x = 255;
	return (x);
}

int32_t				rt_color_channels_to_int(int red, int green, int blue)
{
	uint32_t color;

	color = 0u;
	color |= rt_normalize(red) << 16;
	color |= rt_normalize(green) << 8;
	color |= rt_normalize(blue);
	return (*(int32_t *)&color);
}

int32_t				rt_color_to_int(t_color c)
{
	return (rt_color_channels_to_int(c.red, c.green, c.blue));
}

t_color				rt_init_color(int red, int green, int blue)
{
	t_color c;

	c.red = red;
	c.green = green;
	c.blue = blue;
	return (c);
}

t_color				rt_get_color(t_x intersection)
{
	t_otype objtype;

	if (intersection.object == NULL)
		return (rt_init_color(0, 0, 0));
	objtype = (t_objtype)((t_object *)intersection.object)->type;
	if (objtype == RT_SPHERE)
		return (rt_sphere_color(intersection));
	return (rt_init_color(0, 0, 0));
}
