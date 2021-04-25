/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_quadratic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 22:34:09 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/01 22:34:31 by dpowdere         ###   ########.fr       */
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

double	rt_get_quadratic_root(t_roots r, int *is_inside, double limit);
t_roots	rt_quadratic_equation(double a, double b, double c);

#endif
