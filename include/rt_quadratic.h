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
	t_float	discriminant;
	t_float	root1;
	t_float	root2;
}		t_roots;

t_float	rt_get_quadratic_root(t_roots r);
t_roots	rt_quadratic_equation(t_float a, t_float b, t_float c);

#endif
