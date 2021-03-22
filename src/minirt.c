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
	ft_print("key: ");
	ft_putnbr_fd(keycode, 1);
	ft_print("\n");
	if (keycode == KEY_Q || keycode == KEY_ESQ)
		rt_on_close(scene);
	return (0);
}

void	rt_render_scene(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (scene->mlx == NULL)
		rt_xerror(scene, RT_ERROR_XSERVER, RT_ERROR_XSERVER_MSG);
	scene->window = mlx_new_window(scene->mlx, 900, 600, "miniRT");
	if (scene->window == NULL)
		rt_xerror(scene, RT_ERROR_XWINDOW, RT_ERROR_XWINDOW_MSG);
	mlx_clear_window(scene->mlx, scene->window);
	mlx_pixel_put(scene->mlx, scene->window,
					100, 100, rt_get_color(0, 255, 0, 0));
	mlx_string_put(scene->mlx, scene->window,
					10, 20, rt_get_color(0, 128, 128, 0), "Pixel");
	mlx_hook(scene->window, XEVENT_CLIENT_MESSAGE, XMASK_NO_EVENT,
		rt_on_close, scene);
	mlx_key_hook(scene->window, rt_on_keypress, scene);
	mlx_loop(scene->mlx);
	rt_xerror(scene, RT_ERROR_XLOOP, RT_ERROR_XLOOP_MSG);
}

/*
** For closing a window,
** see https://tronche.com/gui/x/icccm/sec-4.html#s-4.2.8.1
** and WM_DELETE_WINDOW ICCCM protocol.
*/

int		main(int argc, char **argv)
{
	t_scene scene;

	scene = rt_init_scene();
	if (argc != 2)
		rt_error(RT_ERROR_ARGS, RT_ERROR_ARGS_MSG);
	rt_load_scene(argv[1], &scene);
	rt_render_scene(&scene);
	return (0);
}
