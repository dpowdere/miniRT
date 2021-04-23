/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ambient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:58:30 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 12:06:42 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_ambient(t_config_line *c)
{
	if (!isnan(c->scene->ambient))
		rt_scheme_error(c, RT_CONFIG_LINE,
			"Ambient lighting", "Can be specified only once");
	if (c->n_segments != 3)
		rt_parsing_error(c, "Ambient lighting", "Wrong number of arguments");
	c->scene->ambient = rt_parse_float(c, 1, "Ambient lighting intensity");
	if (c->scene->ambient < 0.0 || c->scene->ambient > 1.0)
		rt_scheme_error(c, RT_CONFIG_LINE, "Ambient lighting intensity",
			"Value must be in the range [0.0, 1.0]");
	c->scene->ambient_color = rt_parse_color(c, 2, "Ambient lighting color");
}
