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

static inline int	rt_normalize(int x)
{
	if (x < 0)
		x = 0;
	else if (x > 255)
		x = 255;
	return (x);
}

int32_t				rt_get_color(int red, int green, int blue)
{
	uint32_t color;

	color = 0u;
	color |= rt_normalize(red) << 16;
	color |= rt_normalize(green) << 8;
	color |= rt_normalize(blue);
	return (*(int32_t *)&color);
}
