/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:01:16 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:01:35 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include <mlx.h>
#include <libft.h>

#include "minirt.h"

#define NM "Camera"

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
*/

t_vector	rt_calc_camera_x_orientation(t_vector zo)
{
	t_vector	xo;
	t_float		u_1;
	t_float		u_3;

	u_3 = 0.;
	u_1 = 1.;
	if (zo.x != 0.)
	{
		u_3 = sqrt(1. / (1. + zo.z * zo.z / (zo.x * zo.x)));
		u_1 = sqrt(1 - u_3 * u_3);
	}
	xo = vt_init(u_1, 0., u_3);
	return (xo);
}

void	rt_parse_camera(t_config_line *c)
{
	t_camera	*camera;
	t_list		*list_element;

	if (c->n_segments != 4)
		rt_parsing_error(c, NM, "Wrong number of arguments");
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	camera->origin = rt_parse_vector(c, 1, NM " origin", NON_NORMALIZED);
	camera->z_orientation = rt_parse_vector(c, 2, NM " orientation", NORMALIZED);
	camera->x_orientation = rt_calc_camera_x_orientation(camera->z_orientation);
	camera->y_orientation = vt_mul_dot(camera->z_orientation, camera->x_orientation);
	camera->view_angle = rt_parse_float(c, 3, NM " view angle");
	if (camera->view_angle <= 0.0 || camera->view_angle > 180.0)
		rt_scheme_error(c, RT_CONFIG_LINE,
			NM, "View angle must be in the range (0, 180]");
	camera->viewport = NULL;
	camera->width = NAN;
	camera->height = NAN;
	list_element = ft_lstnew(camera);
	if (list_element == NULL)
	{
		free(camera);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->cameras, list_element);
}

void	rt_init_camera_viewports(t_scene *scene)
{
	t_list		*elem;
	t_camera	*camera;

	elem = scene->cameras;
	while (elem != NULL)
	{
		camera = elem->content;
		camera->viewport = rt_init_image(scene);
		camera->width = TAN(vt_rad(camera->view_angle / 2)) * 2;
		camera->height = camera->width / scene->width * scene->height;
		elem = elem->next;
	}
	scene->active_camera = scene->cameras;
}

void	rt_switch_camera(t_scene *s)
{
	t_list		*elem;
	t_camera	*camera;

	if (s->cameras->next == NULL)
		return ;
	elem = s->active_camera->next;
	if (elem == NULL)
		elem = s->cameras;
	s->active_camera = elem;
	camera = s->active_camera->content;
	mlx_clear_window(s->mlx, s->window);
	mlx_put_image_to_window(s->mlx, s->window, camera->viewport->img, 0, 0);
}

void	rt_free_camera(void *data)
{
	t_camera *const	camera = (t_camera *)data;

	if (camera == NULL)
		return ;
	if (camera->viewport != NULL)
	{
		rt_free_image(camera->viewport);
		camera->viewport = NULL;
	}
	free((void *)camera);
}
