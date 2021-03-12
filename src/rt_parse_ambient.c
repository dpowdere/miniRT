/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:58:30 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 12:06:42 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_ambient(t_config_line *c)
{
	int		intensity;
	char	*endptr;

	if (!isnan(c->scene->ambient))
		rt_parsing_error(c, "Ambient lighting", "Can be specified only once");
	if (c->n_segments != 3)
		rt_parsing_error(c, "Ambient lighting", "Wrong number of arguments");
	endptr = NULL;
	intensity = ft_strtod(c->segments[1], &endptr);
	if (*endptr != '\0' || intensity < 0.0 || intensity > 1.0)
		rt_parsing_error(c, "Ambient lighting intensity", "Invalid value");
	c->scene->ambient = intensity;
	c->scene->ambient_color = rt_parse_color(c, 2, "Ambient lighting color");
}
