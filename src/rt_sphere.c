/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:06:05 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:06:23 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_sphere(t_config_line *c)
{
	t_sphere	*sp;
	t_list		*list_element;

	if (c->n_segments != 4)
		rt_parsing_error(c, "Sphere", "Wrong number of arguments");
	if ((sp = (t_sphere *)malloc(sizeof(t_sphere))) == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(int *)&sp->type = RT_SPHERE;
	sp->location = rt_parse_vector(c, 1, "Sphere location", NON_NORMALIZED);
	sp->diameter = rt_parse_float(c, 2, "Sphere diameter");
	sp->color = rt_parse_color(c, 3, "Sphere color");
	if ((list_element = ft_lstnew(sp)) == NULL)
	{
		free(sp);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}

t_x		rt_sphere_intersection(t_point origin, t_point direction, t_sphere *sp)
{
	const t_vector	dir = vt_add(direction, vt_inv(origin));
	const t_vector	dis = vt_add(origin, vt_inv(sp->location));
	t_float			t;
	t_roots			r;
	t_x				x;

	r = rt_quadratic_equation(
				vt_mul_dot(dir, dir),
				vt_mul_dot(dis, dir) * 2,
				vt_mul_dot(dis, dis) - sp->diameter / 2);
	if (r.discriminant < 0.0)
		return (rt_get_no_intersection(NULL));
	t = rt_get_quadratic_root(r);
	x.object = sp;
	x.point = vt_add(origin, vt_mul_sc(dir, t));
	return (x);
}

t_color	rt_sphere_color(t_x x)
{
	const t_sphere	*sp = x.object;

	if (sp)
		return (sp->color);
	return (rt_init_color(0, 0, 0));
}
