/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_orientation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 09:22:34 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/27 09:22:36 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"

/*
** As we only get camera's Z orientation vector from the scene config file,
** we had to manually choose X and Y orientation vectors. Let X orientation
** vector be parallel to the global XZ plane.
**
** Let X orientation vector be U = (u_1, u_2, u_3) and Z orientation vector
** be W = (w_1, w_2, w_3). Then we have a system of equations:
**
**   (1) u_1^2 + u_3^2 = 1
**   (2) w_1 * u_1 + w_3 * u_3 = 0,
**
** (1) as |U| = 1 and U is parallel to the global XZ plane, and (2) as
** U is perpendicular to W, hence, U \dot W = 0.
**
**   if w_1 != 0, then u_3 = sqrt(1 / (1 + w_3^2 / w_1^2)),
**                     u_1 = +-sqrt(1 - u_3^2)
**   if w_1 = 0, then u_3 = 0, u_1 = +-1.
**
** So that the final orientation of the vector U is properly chosen, we
** must count for the octants W is in or in between:
**
**   w_1 > 0, w_3 > 0  ==>  u_1 > 0, u_3 < 0
**   w_1 < 0, w_3 > 0  ==>  u_1 > 0, u_3 > 0
**   w_1 < 0, w_3 < 0  ==>  u_1 < 0, u_3 > 0
**   w_1 > 0, w_3 < 0  ==>  u_1 < 0, u_3 < 0
**
**   w_1 = 0, w_3 > 0  ==>  u_1 > 0, u_3 = 0
**   w_1 = 0, w_3 < 0  ==>  u_1 < 0, u_3 = 0
**   w_1 > 0, w_3 = 0  ==>  u_1 = 0, u_3 < 0
**   w_1 < 0, w_3 = 0  ==>  u_1 = 0, u_3 > 0
**
**   w_1 = 0, w_2 \neq 0, w_3 = 0  ==>  u_1 = 1, u_3 = 0
**
** And finally u_2 is always zero.
*/

t_vector	rt_zx_orientation(t_vector z_ornt)
{
	double	u1;
	double	u3;

	u3 = 0.;
	if (fabs(z_ornt.x) < EPS && z_ornt.z >= 0)
		u1 = +1.;
	else if (fabs(z_ornt.x) < EPS && z_ornt.z <= -EPS)
		u1 = -1.;
	else if (fabs(z_ornt.z) < EPS)
	{
		u1 = 0.;
		u3 = copysign(1., -z_ornt.x);
	}
	else if (fabs(z_ornt.x) >= EPS)
	{
		u3 = sqrt(1. / (1. + z_ornt.z * z_ornt.z / (z_ornt.x * z_ornt.x)));
		u1 = sqrt(1. - u3 * u3);
		if (z_ornt.x >= EPS && fabs(z_ornt.z) >= EPS)
			u3 = -u3;
		if (fabs(z_ornt.x) >= EPS && z_ornt.z <= -EPS)
			u1 = -u1;
	}
	return (vt_normalize(vt_init(u1, 0., u3)));
}

t_vector	rt_zxy_orientation(t_vector z_ornt, t_vector x_ornt)
{
	return (vt_normalize(vt_mul_cross(z_ornt, x_ornt)));
}
