/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:01:16 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:01:35 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

#define NM "Camera"

void	rt_parse_camera(t_config_line *c)
{
	t_camera	*camera;
	t_list		*list_element;

	if (c->n_segments != 4)
		rt_parsing_error(c, NM, "Wrong number of arguments");
	if ((camera = (t_camera *)malloc(sizeof(t_camera))) == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	camera->location = rt_parse_vector(c, 1, NM " location", NON_NORMALIZED);
	camera->orientation = rt_parse_vector(c, 2, NM " orientation", NORMALIZED);
	camera->view_angle = rt_parse_float(c, 3, NM " view angle");
	if (camera->view_angle <= 0.0 || camera->view_angle > 180.0)
		rt_parsing_error(c, NM, "View angle must be in the range (0, 180]");
	if ((list_element = ft_lstnew(camera)) == NULL)
	{
		free(camera);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->cameras, list_element);
	if (c->scene->active_camera == NULL)
		c->scene->active_camera = camera;
}
