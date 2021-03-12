/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 23:48:40 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/11 23:50:38 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

#define SPACES		" \f\n\r\t\v"
#define IS_ETYPE(e)	(!ft_strcmp((e), cline->segments[0]))

void	rt_parse_type(t_config_line *cline, t_scene *scene)
{
	if (IS_ETYPE("A"))
		rt_parse_ambient(cline, scene);
	else if (IS_ETYPE("c"))
		rt_parse_camera(cline, scene);
	else if (IS_ETYPE("cy"))
		rt_parse_cylinder(cline, scene);
	else if (IS_ETYPE("l"))
		rt_parse_light(cline, scene);
	else if (IS_ETYPE("pl"))
		rt_parse_plane(cline, scene);
	else if (IS_ETYPE("R"))
		rt_parse_resolution(cline, scene);
	else if (IS_ETYPE("sp"))
		rt_parse_sphere(cline, scene);
	else if (IS_ETYPE("sq"))
		rt_parse_square(cline, scene);
	else if (IS_ETYPE("tr"))
		rt_parse_triangle(cline, scene);
	else
	{
		free((void *)cline->segments);
		rt_parse_error(cline, "Unknown element type");
	}
}

void	rt_parse_line(const char *line, size_t line_num, t_scene *scene)
{
	t_config_line	config_line;
	int				i;

	i = 0;
	config_line.line = line;
	config_line.line_num = line_num;
	config_line.segments = (char const *const *)ft_split_const(line, SPACES);
	config_line.n_segments = ft_ptrarr_len((void **)config_line.segments);
	if (config_line.n_segments > 0)
	{
		rt_parse_type(&config_line, scene);
		printf(">>>");
		while (config_line.segments[i])
		{
			printf(" %s", config_line.segments[i]);
			++i;
		}
		printf("\n");
	}
	free((void *)config_line.segments);
}
