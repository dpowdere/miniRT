/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:02:10 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:02:24 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_cylinder(t_config_line *c)
{
	t_cylinder	cy;
	char		*endptr;

	if (c->n_segments != 6)
		rt_parsing_error(c, "Cylinder", "Wrong number of arguments");
	cy.location = rt_parse_vector(c, 1, "Cylinder location");

	cy.orientation = rt_parse_vector(c, 2, "Cylinder orientation");
	// check normalized

	endptr = NULL;
	cy.diameter = ft_strtod(c->segments[3], &endptr);
	if (endptr == NULL || *endptr == '\0')
		rt_parsing_error(c, "Cylinder diameter", "Invalid value");

	cy.height = ft_strtod(c->segments[4], &endptr);
	if (endptr == NULL || *endptr == '\0')
		rt_parsing_error(c, "Cylinder height", "Invalid value");

	cy.color = rt_parse_color(c, 5, "Cylinder color");
}
