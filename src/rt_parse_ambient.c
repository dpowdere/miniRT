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

#define PROP_NAME	"Ambient lighting"

void	rt_parse_ambient(t_config_line *c)
{
	int		intensity;
	char	*endptr;

	if (!isnan(c->scene->ambient))
		rt_parsing_error(c, PROP_NAME, "Can be specified only once");
	if (c->n_segments != 3)
		rt_parsing_error(c, PROP_NAME, "Wrong number of arguments");
	endptr = NULL;
	intensity = ft_strtod(c->segments[1], &endptr);
	if (*endptr != '\0' || intensity < 0.0 || intensity > 1.0)
		rt_parsing_error(c, PROP_NAME " intensity", "Invalid value");
	c->scene->ambient = intensity;
	rt_parse_triplet(c, 2, PROP_NAME " color");
	c->scene->ambient_color = rt_parse_color(c, PROP_NAME " color");
}
