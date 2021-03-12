/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 23:48:40 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 12:55:13 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

#define BASE				10
#define DO_FREE_ERROR_MSG	1
#define IS_ETYPE(e)			(!ft_strcmp((e), cline->segments[0]))
#define SPACES				" \f\n\r\t\v"

void		rt_parse_line(const char *line, size_t line_num, t_scene *scene)
{
	t_config_line	config_line;
	int				i;

	i = 0;
	config_line.line = line;
	config_line.line_num = line_num;
	config_line.segments = (char const *const *)ft_split_const(line, SPACES);
	config_line.n_segments = ft_ptrarr_len((void **)config_line.segments);
	config_line.triplet = NULL;
	config_line.scene = scene;
	if (config_line.n_segments > 0)
	{
		rt_parse_type(&config_line);
		printf(">>>");
		while (config_line.segments[i])
		{
			printf(" %s", config_line.segments[i]);
			++i;
		}
		printf("\n");
	}
	rt_config_line_regular_free(&config_line);
}

void		rt_parse_type(t_config_line *cline)
{
	if (IS_ETYPE("A"))
		rt_parse_ambient(cline);
	else if (IS_ETYPE("c"))
		rt_parse_camera(cline);
	else if (IS_ETYPE("cy"))
		rt_parse_cylinder(cline);
	else if (IS_ETYPE("l"))
		rt_parse_light(cline);
	else if (IS_ETYPE("pl"))
		rt_parse_plane(cline);
	else if (IS_ETYPE("R"))
		rt_parse_resolution(cline);
	else if (IS_ETYPE("sp"))
		rt_parse_sphere(cline);
	else if (IS_ETYPE("sq"))
		rt_parse_square(cline);
	else if (IS_ETYPE("tr"))
		rt_parse_triangle(cline);
	else
		rt_parsing_error(cline, NULL, "Unknown element type");
}

void		rt_parse_triplet(t_config_line *c, int segnum, const char *segname)
{
	c->triplet = (char const *const *)ft_split_const(c->segments[segnum], ",");
	if (3 != ft_ptrarr_len((void **)c->triplet))
		rt_parsing_error(c, segname, "Wrong number of constituents");
}

t_color		rt_parse_color(t_config_line *c, const char *attrname)
{
	t_color	color;
	char	*endptr;

	endptr = NULL;
	color.red = ft_strtoi(c->triplet[0], &endptr, BASE);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, attrname, "Invalid value for red channel");
	color.green = ft_strtoi(c->triplet[1], &endptr, BASE);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, attrname, "Invalid value for green channel");
	color.blue = ft_strtoi(c->triplet[2], &endptr, BASE);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, attrname, "Invalid value for blue channel");
	if (color.red < 0 || color.red > 255 ||
			color.green < 0 || color.green > 255 ||
			color.blue < 0 || color.blue > 255)
		rt_parsing_error(c, attrname,
				"Each color channel value must be in the range [0, 255]");
	return (color);
}
