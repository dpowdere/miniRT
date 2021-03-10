/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:55:37 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/03 23:03:25 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>
# include "rt_keys.h"

typedef struct	s_scene
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}				t_scene;

int32_t			rt_get_color(int alpha, int red, int green, int blue);

#endif
