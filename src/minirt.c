/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 22:36:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/11 18:58:46 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <mlx.h>
#include <libft.h>

#include "minirt.h"
#include "rt_events.h"

int		rt_on_close(t_scene *scene)
{
	rt_free_scene(scene);
	exit(0);
}

int		rt_on_keypress(int keycode, t_scene *scene)
{
	if (keycode == KEY_Q || keycode == KEY_ESQ)
		rt_on_close(scene);
	return (0);
}

void	rt_draw_smth(t_image *img)
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
			red = 0;
			green = 0;
			blue = 0;
			if (u > img->scene->width / 2)
				red = 255;
			if (v > img->scene->height / 2)
				green = 255;
			rt_put_pixel(img, u, v, rt_get_color(red, green, blue));
		}
	}
}

void	rt_render_scene(t_scene *s)
{
	t_image *img;

	img = rt_init_image(s);
	rt_draw_smth(img);
	s->window = mlx_new_window(s->mlx, s->width, s->height, "miniRT");
	if (s->window == NULL)
		rt_xerror(s, RT_ERROR_XWINDOW, RT_ERROR_XWINDOW_MSG);
	mlx_clear_window(s->mlx, s->window);
	mlx_put_image_to_window(s->mlx, s->window, img->img, 0, 0);
	mlx_hook(s->window, XEVENT_CLIENT_MESSAGE, XMASK_NO_EVENT, rt_on_close, s);
	mlx_key_hook(s->window, rt_on_keypress, s);
	mlx_loop(s->mlx);
	rt_xerror(s, RT_ERROR_XLOOP, RT_ERROR_XLOOP_MSG);
}

/*
** NOTE: For closing a window see `ClientMessage` X event
** https://tronche.com/gui/x/xlib/events/ and `WM_DELETE_WINDOW` ICCCM
** protocol https://tronche.com/gui/x/icccm/sec-4.html#s-4.2.8.1
*/

int		main(int argc, char **argv)
{
	t_scene scene;

	if (argc != 2)
		rt_error(RT_ERROR_ARGS, RT_ERROR_ARGS_MSG);
	scene = rt_init_scene();
	rt_load_scene(argv[1], &scene);
	rt_render_scene(&scene);
	return (0);
}
