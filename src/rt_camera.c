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

#define OBJECT		"Camera"
#define ORIG_PROP	"Camera origin"
#define ORNT_PROP	"Camera orientation"
#define VANG_PROP	"Camera view angle"
#define VANG_EMSG	"View angle must be in the range (0, 180]"

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

t_vector	rt_calc_camera_x_orientation(t_vector z_ornt)
{
	t_float		u1;
	t_float		u3;

	u3 = 0.;
	if (z_ornt.x == 0 && z_ornt.z >= 0)
		u1 = +1.;
	else if (z_ornt.x == 0 && z_ornt.z < 0)
		u1 = -1.;
	else if (z_ornt.z == 0)
	{
		u1 = 0.;
		if (z_ornt.x > 0)
			u3 = -1.;
		else if (z_ornt.x < 0)
			u3 = +1.;
	}
	else if (z_ornt.x != 0.)
	{
		u3 = sqrt(1. / (1. + z_ornt.z * z_ornt.z / (z_ornt.x * z_ornt.x)));
		u1 = sqrt(1. - u3 * u3);
		if (z_ornt.x > 0 && (z_ornt.z > 0 && z_ornt.z < 0))
			u3 = -u3;
		if ((z_ornt.x < 0 || z_ornt.x > 0) && z_ornt.z < 0)
			u1 = -u1;
	}
	return (vt_init(u1, 0., u3));
}

void	rt_parse_camera(t_config_line *c)
{
	t_camera	*camera;
	t_list		*list_element;

	if (c->n_segments != 4)
		rt_parsing_error(c, OBJECT, "Wrong number of arguments");
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	camera->origin = rt_parse_vector(c, 1, ORIG_PROP, NON_NORMALIZED);
	camera->z_ornt = rt_parse_vector(c, 2, ORNT_PROP, NORMALIZED);
	camera->x_ornt = rt_calc_camera_x_orientation(camera->z_ornt);
	camera->y_ornt = vt_mul_cross(camera->z_ornt, camera->x_ornt);
	camera->view_angle = rt_parse_float(c, 3, VANG_PROP);
	if (camera->view_angle <= 0.0 || camera->view_angle > 180.0)
		rt_scheme_error(c, RT_CONFIG_LINE, OBJECT, VANG_EMSG);
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
