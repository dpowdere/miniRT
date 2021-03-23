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

#include <libft.h>

#include "minirt.h"

#define BASE		10
#define IS_ETYPE(e)	(!ft_strcmp((e), cline->segments[0]))

void		rt_parse_type(t_config_line *cline)
{
	if ('#' == *cline->segments[0])
		return ;
	else if (IS_ETYPE("A"))
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

void		rt_parse_triplet(t_config_line *c, int ix, const char *scope_name)
{
	c->triplet = (char const *const *)ft_split_const(c->segments[ix], ",");
	if (3 != ft_ptrarr_len((void **)c->triplet))
		rt_parsing_error(c, scope_name, "Wrong number of constituents");
}

double		rt_parse_float(t_config_line *c, int ix, const char *scope_name)
{
	char	*endptr;
	double	value;

	endptr = NULL;
	value = ft_strtod(c->segments[ix], &endptr);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, scope_name, "Invalid value");
	return (value);
}

t_color		rt_parse_color(t_config_line *c, int ix, const char *scope_name)
{
	t_color	color;
	char	*endptr;

	endptr = NULL;
	rt_parse_triplet(c, ix, scope_name);
	color.red = ft_strtoi(c->triplet[0], &endptr, BASE);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, scope_name, "Red channel: Invalid value");
	color.green = ft_strtoi(c->triplet[1], &endptr, BASE);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, scope_name, "Green channel: Invalid value");
	color.blue = ft_strtoi(c->triplet[2], &endptr, BASE);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, scope_name, "Blue channel: Invalid value");
	if (color.red < 0 || color.red > 255 ||
			color.green < 0 || color.green > 255 ||
			color.blue < 0 || color.blue > 255)
		rt_scheme_error(c, RT_CONFIG_LINE, scope_name,
				"Color channels must have values in the range [0, 255]");
	return (color);
}

t_vector	rt_parse_vector(t_config_line *c, int ix, const char *scope_name,
							int should_be_normalized)
{
	t_vector	vec;
	char		*endptr;

	endptr = NULL;
	rt_parse_triplet(c, ix, scope_name);
	vec.x = ft_strtod(c->triplet[0], &endptr);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, scope_name, "X attribute: Invalid value");
	vec.y = ft_strtod(c->triplet[1], &endptr);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, scope_name, "Y attribute: Invalid value");
	vec.z = ft_strtod(c->triplet[2], &endptr);
	if (endptr == NULL || *endptr != '\0')
		rt_parsing_error(c, scope_name, "Z attribute: Invalid value");
	if (should_be_normalized && (vec.x < -1.0 || vec.x > 1.0 ||
				vec.y < -1.0 || vec.y > 1.0 || vec.z < -1.0 || vec.z > 1.0))
		rt_scheme_error(c, RT_CONFIG_LINE, scope_name,
				"Individual values must be in the range [-1, 1]");
	return (vec);
}
