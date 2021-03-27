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

#include <mlx.h>
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
		rt_scheme_error(c, RT_CONFIG_LINE,
						NM, "View angle must be in the range (0, 180]");
	camera->viewport = NULL;
	if ((list_element = ft_lstnew(camera)) == NULL)
	{
		free(camera);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->cameras, list_element);
}

void	rt_draw_smth(t_image *img, int i)
{
	int	u;
	int	v;
	int	red;
	int	green;
	int	blue;

	u = img->scene->width;
	while (--u >= 0)
	{
		v = img->scene->height;
		while (--v >= 0)
		{
			red = (long)img % 256;
			green = ((long)img + 85 * i) % 256;
			blue = ((long)img + 190 * i) % 256;
			if (u > img->scene->width / 4)
				red = ((long)img + 128 * i) % 256;
			if (v > img->scene->height / 4)
				green = ((long)img + 190 * i) % 256;
			rt_put_pixel(img, u, v, rt_get_color(red, green, blue));
		}
	}
}

void	rt_init_camera_viewports(t_scene *scene)
{
	t_list		*elem;
	t_camera	*camera;
	int			i;

	i = 1;
	elem = scene->cameras;
	while (elem != NULL)
	{
		camera = elem->content;
		camera->viewport = rt_init_image(scene);
		rt_draw_smth(camera->viewport, i++);
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
	t_camera *const camera = (t_camera *)data;

	if (camera == NULL)
		return ;
	if (camera->viewport != NULL)
	{
		rt_free_image(camera->viewport);
		camera->viewport = NULL;
	}
	free((void *)camera);
}
