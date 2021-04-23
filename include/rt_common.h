/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_common.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 22:33:52 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/01 22:34:05 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_COMMON_H
# define RT_COMMON_H

# include <math.h>

typedef double	t_float;

# define ACOS		acos
# define COPYSIGN	copysign
# define FABS		fabs
# define FMOD		fmod
# define SQRT		sqrt
# define TAN		tan

# define PI			ACOS(-1.)
# define PI_2		ACOS(0.)

# define EPS	1.11e-16

# define FT_STRTOF	ft_strtod

# define AEC_ERASE_EOL		"\033[0K"
# define AEC_ERASE_LINE		"\033[2K"
# define AEC_HIDE_CURSOR	"\033[?25l"
# define AEC_SHOW_CURSOR	"\033[?25h"

# define TRUE	1
# define FALSE	0

#endif
