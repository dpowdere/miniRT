/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:06:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:07:09 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_square(t_config_line *c)
{
	t_square	*sq;
	t_list		*list_element;

	if (c->n_segments != 5)
		rt_parsing_error(c, "Square", "Wrong number of arguments");
	sq = (t_square *)malloc(sizeof(t_square));
	if (sq == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(t_otype *)&sq->type = RT_SQUARE;
	sq->origin = rt_parse_vector(c, 1, "Square origin", NON_NORMALIZED);
	sq->z_ornt = rt_parse_vector(c, 2, "Square orientation", NORMALIZED);
	sq->x_ornt = vt_zx_orientation(sq->z_ornt);
	sq->y_ornt = vt_zxy_orientation(sq->z_ornt, sq->x_ornt);
	sq->half_side_size = rt_parse_float(c, 3, "Square side size") / 2.;
	sq->color = rt_parse_color(c, 4, "Square color");
	list_element = ft_lstnew(sq);
	if (list_element == NULL)
	{
		free(sq);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}

t_x	rt_square_intersection(t_ray ray, t_square *sq, double limit)
{
	t_vector	p;
	t_plane		pl;
	t_x			pl_x;
	t_x			x;

	*(t_otype *)&pl.type = (t_objtype)RT_PLANE;
	pl.origin = sq->origin;
	pl.orientation = sq->z_ornt;
	pl.color = sq->color;
	pl_x = rt_plane_intersection(ray, &pl, limit);
	x = rt_get_no_intersection(ray, sq);
	if (vt_isinf(pl_x.point))
		return (x);
	p = vt_add(pl_x.point, vt_inv(sq->origin));
	if (fabs(vt_proj_alg(p, sq->x_ornt)) - sq->half_side_size >= EPS
		|| fabs(vt_proj_alg(p, sq->y_ornt)) - sq->half_side_size >= EPS)
		return (x);
	pl_x.object = sq;
	return (pl_x);
}

void	rt_square_normal(t_x *x)
{
	const t_square	*sq = x->object;

	x->normal = sq->z_ornt;
	if (x->is_flip_side)
		x->normal = vt_inv(sq->z_ornt);
}
