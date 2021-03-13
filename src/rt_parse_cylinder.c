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
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

#define NORMALIZED		1
#define NON_NORMALIZED	0

void	rt_parse_cylinder(t_config_line *c)
{
	t_cylinder	*cy;
	t_list		*list_element;

	if (c->n_segments != 6)
		rt_parsing_error(c, "Cylinder", "Wrong number of arguments");
	if ((cy = (t_cylinder *)malloc(sizeof(t_cylinder))) == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(int *)&cy->type = RT_CYLINDER;
	cy->location = rt_parse_vector(c, 1, "Cylinder location", NON_NORMALIZED);
	cy->orientation = rt_parse_vector(c, 2, "Cylinder orientation", NORMALIZED);
	cy->diameter = rt_parse_float(c, 3, "Cylinder diameter");
	cy->height = rt_parse_float(c, 4, "Cylinder height");
	cy->color = rt_parse_color(c, 5, "Cylinder color");
	if ((list_element = ft_lstnew(cy)) == NULL)
	{
		free(cy);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}
