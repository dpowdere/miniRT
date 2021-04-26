/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:04:05 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:04:19 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_plane(t_config_line *c)
{
	t_plane	*pl;
	t_list	*list_element;

	if (c->n_segments != 4)
		rt_parsing_error(c, "Plane", "Wrong number of arguments");
	pl = (t_plane *)malloc(sizeof(t_plane));
	if (pl == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(int *)&pl->type = RT_PLANE;
	pl->origin = rt_parse_vector(c, 1, "Plane origin", NON_NORMALIZED);
	pl->orientation = rt_parse_vector(c, 2, "Plane orientation", NORMALIZED);
	pl->color = rt_parse_color(c, 3, "Plane color");
	list_element = ft_lstnew(pl);
	if (list_element == NULL)
	{
		free(pl);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}

t_x	rt_plane_intersection(t_ray ray, t_plane *pl, double limit)
{
	const t_scalar	a = vt_mul_dot(ray.orientation, pl->orientation);
	t_scalar		b;
	double			t;
	t_x				x;

	x = rt_get_no_intersection(ray, pl);
	if (fabs(a) < EPS)
		return (x);
	b = vt_mul_dot(vt_add(ray.origin, vt_inv(pl->origin)), pl->orientation);
	if (fabs(b) < EPS)
		return (x);
	t = -b / a;
	if (t < EPS || limit - t < EPS)
		return (x);
	if (b <= -EPS)
		x.is_flip_side = TRUE;
	x.point = vt_add(ray.origin, vt_mul_sc(ray.orientation, t));
	x.color = pl->color;
	return (x);
}

void	rt_plane_normal(t_x *x)
{
	const t_plane	*pl = x->object;

	if (pl == NULL)
		return ;
	x->normal = pl->orientation;
	if (x->is_flip_side)
		x->normal = vt_inv(pl->orientation);
}
