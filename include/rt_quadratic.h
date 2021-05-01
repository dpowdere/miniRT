/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_quadratic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 22:34:09 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/01 19:05:33 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_QUADRATIC_H
# define RT_QUADRATIC_H

# include "rt_common.h"

typedef struct s_quadratic_equation_roots
{
	double	discriminant;
	double	root1;
	double	root2;
}		t_roots;

typedef struct s_moeller_trumbore
{
	t_vector	e1;
	t_vector	e2;
	t_vector	h;
	t_vector	s;
	t_vector	q;
	t_scalar	a;
	t_scalar	f;
	t_scalar	u;
	t_scalar	v;
	t_scalar	t;
	t_x			x;
}		t_mt;

double	rt_get_quadratic_root(t_roots r, int *is_inside, double limit);
t_roots	rt_quadratic_equation(double a, double b, double c);

#endif
