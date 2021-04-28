/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:02:10 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/28 20:07:47 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_cylinder(t_config_line *c)
{
	t_cylinder	*cy;
	t_list		*list_element;

	if (c->n_segments != 6)
		rt_parsing_error(c, "Cylinder", "Wrong number of arguments");
	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cy == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(int *)&cy->type = RT_CYLINDER;
	cy->origin = rt_parse_vector(c, 1, "Cylinder origin", NON_NORMALIZED);
	cy->orientation = rt_parse_vector(c, 2, "Cylinder orientation", NORMALIZED);
	cy->diameter = rt_parse_float(c, 3, "Cylinder diameter");
	cy->height = rt_parse_float(c, 4, "Cylinder height");
	cy->color = rt_parse_color(c, 5, "Cylinder color");
	list_element = ft_lstnew(cy);
	if (list_element == NULL)
	{
		free(cy);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}

t_x	rt_cylinder_intersection(t_ray ray, t_plane *pl, double limit)
{
	t_x	x;

	(void)limit;
	x = rt_get_no_intersection(ray, pl);
	return (x);
}

void	rt_cylinder_normal(t_x *x)
{
	const t_cylinder	*cy = x->object;
	t_vector			a;
	t_vector			normal;

	if (cy == NULL)
		return ;
	a = vt_add(x->point, vt_inv(cy->origin));
	a = vt_mul_sc(cy->orientation, vt_mul_dot(a, cy->orientation));
	a = vt_add(a, vt_add(x->point, vt_inv(a)));
	normal = vt_normalize(a);
	if (x->is_flip_side)
		normal = vt_inv(normal);
	x->normal = normal;
}
