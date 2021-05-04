/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:44:50 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/04 23:04:02 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "minirt.h"

int32_t	rt_color_to_int(t_color c)
{
	uint32_t	color;

	color = (uint32_t)0;
	color |= (uint32_t)c.red << 16;
	color |= (uint32_t)c.green << 8;
	color |= (uint32_t)c.blue;
	return (*(int32_t *)&color);
}

t_color	rt_init_color(int red, int green, int blue)
{
	t_color	c;

	if (red < 0)
		red = 0;
	else if (red > 255)
		red = 255;
	if (green < 0)
		green = 0;
	else if (green > 255)
		green = 255;
	if (blue < 0)
		blue = 0;
	else if (blue > 255)
		blue = 255;
	c.red = red;
	c.green = green;
	c.blue = blue;
	return (c);
}

t_color	rt_color_brightness(t_color color, double brightness)
{
	if (brightness < 0.)
		brightness = 0.;
	color.red *= brightness;
	color.green *= brightness;
	color.blue *= brightness;
	if (color.red > 255)
		color.red = 255;
	if (color.green > 255)
		color.green = 255;
	if (color.blue > 255)
		color.blue = 255;
	return (color);
}

t_color	rt_color_merge(t_color c1, t_color c2)
{
	c1.red = (c1.red * c2.red) / 255;
	c1.green = (c1.green * c2.green) / 255;
	c1.blue = (c1.blue * c2.blue) / 255;
	return (c1);
}

t_color	rt_color_add(t_color c1, t_color c2)
{
	c1.red += c2.red;
	c1.green += c2.green;
	c1.blue += c2.blue;
	if (c1.red > 255)
		c1.red = 255;
	if (c1.green > 255)
		c1.green = 255;
	if (c1.blue > 255)
		c1.blue = 255;
	return (c1);
}
