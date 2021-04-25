/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 04:00:52 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/25 04:01:22 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"

int	vt_isinf(t_vector v)
{
	return (isinf(v.x) || isinf(v.y) || isinf(v.z));
}

int	vt_isequal(t_vector a, t_vector b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

/*
** Convert degrees to radians
*/

double	vt_rad(double deg)
{
	return (deg / 180. * acos(-1.));
}
