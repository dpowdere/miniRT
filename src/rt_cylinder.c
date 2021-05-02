/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:02:10 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/01 17:59:40 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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
	*(t_otype *)&cy->type = RT_CYLINDER;
	cy->origin = rt_parse_vector(c, 1, "Cylinder origin", NON_NORMALIZED);
	cy->orientation = rt_parse_vector(c, 2, "Cylinder orientation", NORMALIZED);
	cy->radius = rt_parse_float(c, 3, "Cylinder diameter") / 2.;
	cy->half_height = rt_parse_float(c, 4, "Cylinder height") / 2.;
	cy->color = rt_parse_color(c, 5, "Cylinder color");
	list_element = ft_lstnew(cy);
	if (list_element == NULL)
	{
		free(cy);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}

static inline t_roots	rt__calc_quadeq(t_ray ray, t_cylinder *cy)
{
	const t_vector	ab = vt_add(ray.origin, vt_inv(cy->origin));
	t_vector		alpha;
	t_vector		beta;
	t_roots			r;

	alpha = vt_add(ray.orientation,
			vt_inv(vt_mul_sc(cy->orientation,
					vt_mul_dot(ray.orientation, cy->orientation))));
	beta = vt_add(ab,
			vt_inv(vt_mul_sc(cy->orientation,
					vt_mul_dot(ab, cy->orientation))));
	r = rt_quadratic_equation(
			vt_mul_dot(alpha, alpha),
			vt_mul_dot(alpha, beta) * 2,
			vt_mul_dot(beta, beta) - cy->radius * cy->radius);
	return (r);
}

static inline t_x	rt__finite_cylinder(
						t_ray ray, t_cylinder *cy, t_roots r, double t)
{
	t_x				x;
	t_vector		vec;
	t_point			point;

	x = rt_get_no_intersection(ray, cy);
	point = vt_add(ray.origin, vt_mul_sc(ray.orientation, t));
	vec = vt_add(point, vt_inv(cy->origin));
	vec = vt_mul_sc(cy->orientation, vt_mul_dot(vec, cy->orientation));
	if (vt_magnitude(vec) - cy->half_height >= EPS)
	{
		if (t == r.root1 || r.discriminant < EPS)
			return (x);
		else
		{
			t = r.root1;
			point = vt_add(ray.origin, vt_mul_sc(ray.orientation, t));
			vec = vt_add(point, vt_inv(cy->origin));
			vec = vt_mul_sc(cy->orientation, vt_mul_dot(vec, cy->orientation));
			if (vt_magnitude(vec) - cy->half_height >= EPS)
				return (x);
			x.is_flip_side = TRUE;
		}
	}
	x.point = point;
	return (x);
}

/*
** https://mrl.cs.nyu.edu/~dzorin/rend05/lecture2.pdf
*/
t_x	rt_cylinder_intersection(t_ray ray, t_cylinder *cy, double limit)
{
	t_x				x;
	t_roots			r;
	double			t;

	r = rt__calc_quadeq(ray, cy);
	x = rt_get_no_intersection(ray, cy);
	if (r.discriminant <= -EPS)
		return (x);
	t = rt_get_quadratic_root(r, &x.is_flip_side, limit);
	if (isnan(t))
		return (x);
	x = rt__finite_cylinder(ray, cy, r, t);
	x.color = cy->color;
	return (x);
}

void	rt_cylinder_normal(t_x *x)
{
	const t_cylinder	*cy = x->object;
	t_vector			a;
	t_vector			b;
	t_vector			normal;

	if (cy == NULL)
		return ;
	a = vt_add(x->point, vt_inv(cy->origin));
	b = vt_mul_sc(cy->orientation, vt_mul_dot(a, cy->orientation));
	normal = vt_normalize(vt_add(a, vt_inv(b)));
	if (x->is_flip_side)
		normal = vt_inv(normal);
	x->normal = normal;
}
