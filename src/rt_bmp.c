/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:20:23 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/24 16:21:46 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "minirt.h"

#define FILEPREFIX	"view_"

void	rt_save_bmp(t_image *image, int *serial_number)
{
	(void)image;
	(void)serial_number;
}

void	rt_save_to_bmp_files(t_scene *scene)
{
	t_list		*elem;
	t_camera	*camera;
	int			serial_number;

	serial_number = 1;
	elem = scene->cameras;
	while (elem != NULL)
	{
		camera = elem->content;
		rt_save_bmp(camera->viewport, &serial_number);
		++serial_number;
	}
}
