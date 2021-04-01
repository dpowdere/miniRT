/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_quadratic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 22:34:36 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/01 22:34:53 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"

t_roots	rt_quadratic_equation(t_float a, t_float b, t_float c)
{
	t_roots	roots;

	(void)a;
	(void)b;
	(void)c;
	roots.n = 0;
	roots.a = NAN;
	roots.b = NAN;
	return (roots);
}
