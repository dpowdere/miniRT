/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:04:59 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:05:32 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include <libft.h>

#include "minirt.h"

#define BASE 10

void	rt_parse_resolution(t_config_line *c)
{
	int		width;
	int		height;
	char	*endptr;

	if (c->scene->width != UNDEFINED || c->scene->height != UNDEFINED)
		rt_parsing_error(c, "Resolution can be specified only once");
	if (c->n_segments != 3)
		rt_parsing_error(c, "Resolution config option has "
							"a wrong number of args");
	endptr = NULL;
	width = ft_strtoi(c->segments[1], &endptr, BASE);
	if (*endptr != '\0' || width < 1)
		rt_parsing_error(c, "Invalid config value for resolution width");
	c->scene->width = width;
	height = ft_strtoi(c->segments[2], &endptr, BASE);
	if (*endptr != '\0' || height < 1)
		rt_parsing_error(c, "Invalid config value for resolution height");
	c->scene->height = height;
}
