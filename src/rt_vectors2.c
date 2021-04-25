/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 03:58:15 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/25 03:58:54 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vt_add(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vector	vt_inv(t_vector v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_vector	vt_mul_sc(t_vector v, t_scalar k)
{
	v.x = k * v.x;
	v.y = k * v.y;
	v.z = k * v.z;
	return (v);
}

t_scalar	vt_mul_dot(t_vector v, t_vector w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_vector	vt_mul_cross(t_vector v, t_vector w)
{
	t_vector	r;

	r.x = v.y * w.z - v.z * w.y;
	r.y = v.z * w.x - v.x * w.z;
	r.z = v.x * w.y - v.y * w.x;
	return (r);
}
