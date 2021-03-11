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
#define IS_ETYPE(e)	(!ft_strcmp((e), segments[0]))

void	rt_parse_type(char *const *segments, size_t n, t_scene *scene)
{
	if (IS_ETYPE("A"))
		rt_parse_ambient(segments, n, scene);
	else if (IS_ETYPE("c"))
		rt_parse_camera(segments, n, scene);
	else if (IS_ETYPE("cy"))
		rt_parse_cylinder(segments, n, scene);
	else if (IS_ETYPE("l"))
		rt_parse_light(segments, n, scene);
	else if (IS_ETYPE("pl"))
		rt_parse_plane(segments, n, scene);
	else if (IS_ETYPE("R"))
		rt_parse_resolution(segments, n, scene);
	else if (IS_ETYPE("sp"))
		rt_parse_sphere(segments, n, scene);
	else if (IS_ETYPE("sq"))
		rt_parse_square(segments, n, scene);
	else if (IS_ETYPE("tr"))
		rt_parse_triangle(segments, n, scene);
	else
	{
		free((void *)segments);
		rt_error(RT_ERROR_PARSE_UNKNOWN, RT_ERROR_PARSE_UNKNOWN_MSG);
	}
}

void	rt_parse_line(const char *line, t_scene *scene)
{
	char *const	*segments;
	size_t		n;
	int			i;

	i = 0;
	segments = ft_split_const(line, SPACES);
	n = ft_ptrarr_len((void **)segments);
	if (n > 0)
	{
		rt_parse_type(segments, n, scene);
		printf(">>>");
		while (segments[i])
		{
			printf(" %s", segments[i]);
			++i;
		}
		printf("\n");
	}
	free((void *)segments);
}
