/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:07:34 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/01 19:05:38 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_triangle(t_config_line *c)
{
	t_triangle	*tr;
	t_list		*list_element;

	if (c->n_segments != 5)
		rt_parsing_error(c, "Triangle", "Wrong number of arguments");
	tr = (t_triangle *)malloc(sizeof(t_triangle));
	if (tr == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(t_otype *)&tr->type = RT_TRIANGLE;
	tr->p1 = rt_parse_vector(c, 1, "Triangle, point 1", NON_NORMALIZED);
	tr->p2 = rt_parse_vector(c, 2, "Triangle, point 2", NON_NORMALIZED);
	tr->p3 = rt_parse_vector(c, 3, "Triangle, point 3", NON_NORMALIZED);
	tr->color = rt_parse_color(c, 4, "Triangle color");
	list_element = ft_lstnew(tr);
	if (list_element == NULL)
	{
		free(tr);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}

/*
** The Moeller–Trumbore ray-triangle intersection algorithm, a fast method for
** calculating the intersection of a ray and a triangle in three dimensions
** without needing precomputation of the plane equation of the plane containing
** the triangle. It uses the barycentric coordinates of an intersection point.
**
**   $  O + tD = (1 - u - v) V_0 + u V_1 + v V_2  $
**
** See https://cadxfem.org/inf/
** Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
*/
t_x	rt_triangle_intersection(t_ray ray, t_triangle *tr, double limit)
{
	static t_mt	mt;

	mt.e1 = vt_add(tr->p2, vt_inv(tr->p1));
	mt.e2 = vt_add(tr->p3, vt_inv(tr->p1));
	mt.h = vt_mul_cross(ray.orientation, mt.e2);
	mt.a = vt_mul_dot(mt.e1, mt.h);
	mt.x = rt_get_no_intersection(ray, tr);
	if (fabs(mt.a) < EPS)
		return (mt.x);
	mt.f = 1. / mt.a;
	mt.s = vt_add(ray.origin, vt_inv(tr->p1));
	mt.u = mt.f * vt_mul_dot(mt.s, mt.h);
	if (mt.u < 0. || mt.u > 1.)
		return (mt.x);
	mt.q = vt_mul_cross(mt.s, mt.e1);
	mt.v = mt.f * vt_mul_dot(ray.orientation, mt.q);
	if (mt.v < 0. || mt.u + mt.v > 1.)
		return (mt.x);
	mt.t = mt.f * vt_mul_dot(mt.e2, mt.q);
	if (mt.t > EPS && mt.t < limit)
	{
		mt.x.point = vt_add(ray.origin, vt_mul_sc(ray.orientation, mt.t));
		mt.x.color = tr->color;
	}
	return (mt.x);
}

void	rt_triangle_normal(t_x *x)
{
	const t_triangle	*tr = x->object;
	const t_vector		e1 = vt_add(tr->p2, vt_inv(tr->p1));
	const t_vector		e2 = vt_add(tr->p3, vt_inv(tr->p1));
	t_vector			normal;

	normal = vt_normalize(vt_mul_cross(e1, e2));
	if (vt_cos_angle(normal, x->ray.orientation) < EPS)
		normal = vt_inv(normal);
	x->normal = normal;
}
