/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 22:36:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/01 22:39:03 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <mlx.h>
#include <libft.h>

#include "minirt.h"

int		rt_on_keypress(int keycode, t_scene *scene)
{
	ft_print("key: ");
	ft_putnbr_fd(keycode, 1);
	ft_print("\n");
	if (keycode == KEY_Q || keycode == KEY_ESQ)
	{
		mlx_destroy_window(scene->mlx, scene->window);
		exit(0);
	}
	return (0);
}

void	rt_error(int error_code, char *error_msg)
{
	ft_eprintln("Error");
	ft_eprintln(error_msg);
	exit(error_code);
}

int		main(void)
{
	t_scene scene;

	scene.mlx = mlx_init();
	if (scene.mlx == NULL)
		rt_error(1, "Can't establish connection with display server");
	scene.window = mlx_new_window(scene.mlx, 900, 600, "miniRT");
	if (scene.window == NULL)
		rt_error(2, "Can't display a window");
	mlx_clear_window(scene.mlx, scene.window);
	mlx_pixel_put(scene.mlx, scene.window,
					100, 100, rt_get_color(128, 255, 0, 0));
	mlx_string_put(scene.mlx, scene.window,
					10, 20, rt_get_color(255, 128, 128, 0), "Pixel");
	mlx_key_hook(scene.window, rt_on_keypress, &scene);
	mlx_loop(scene.mlx);
	rt_error(3, "Can't enter the main loop");
	return (3);
}
