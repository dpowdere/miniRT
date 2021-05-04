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

t_camera	*rt_init_camera(t_config_line *c)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	camera->origin = vt_init(NAN, NAN, NAN);
	camera->x_ornt = vt_init(NAN, NAN, NAN);
	camera->y_ornt = vt_init(NAN, NAN, NAN);
	camera->z_ornt = vt_init(NAN, NAN, NAN);
	camera->view_angle = NAN;
	camera->viewport = NULL;
	camera->width = NAN;
	camera->height = NAN;
	camera->horizontal_angle = NAN;
	camera->vertical_angle = NAN;
	camera->horizontal_start = NAN;
	camera->vertical_start = NAN;
	camera->pixel_size = NAN;
	return (camera);
}

void	rt_parse_camera(t_config_line *c)
{
	t_camera	*camera;
	t_list		*list_element;

	if (c->n_segments != 4)
		rt_parsing_error(c, OBJECT, "Wrong number of arguments");
	camera = rt_init_camera(c);
	camera->origin = rt_parse_vector(c, 1, ORIG_PROP, NON_NORMALIZED);
	camera->z_ornt = rt_parse_vector(c, 2, ORNT_PROP, NORMALIZED);
	camera->x_ornt = vt_zx_orientation(camera->z_ornt);
	camera->y_ornt = vt_zxy_orientation(camera->z_ornt, camera->x_ornt);
	camera->view_angle = rt_parse_float(c, 3, VANG_PROP);
	if (camera->view_angle <= 0.0 || camera->view_angle > 180.0)
		rt_scheme_error(c, RT_CONFIG_LINE, OBJECT, VANG_EMSG);
	list_element = ft_lstnew(camera);
	if (list_element == NULL)
	{
		free(camera);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->cameras, list_element);
	c->scene->number_of_cameras += 1;
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
		camera->horizontal_angle = vt_rad(camera->view_angle);
		camera->pixel_size = camera->horizontal_angle / scene->width;
		camera->vertical_angle = camera->pixel_size * scene->height;
		camera->horizontal_start = acos(-1)
			- (acos(-1) - camera->horizontal_angle + camera->pixel_size) / 2.;
		camera->vertical_start = \
			(acos(-1) - camera->vertical_angle + camera->pixel_size) / 2.;
		camera->width = tan(camera->horizontal_angle / 2.) * 2.;
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
