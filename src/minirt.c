/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 22:36:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/05 00:13:19 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

/*
** stddef.h - NULL
** stdlib.h - exit, free
*/

#include <mlx.h>
#include <libft.h>

#include "minirt.h"
#include "rt_events.h"

int	rt_on_close(t_scene *scene)
{
	rt_free_scene(scene);
	exit(0);
}

int	rt_on_keypress(int keycode, t_scene *scene)
{
	if (keycode == KEY_Q || keycode == KEY_ESQ)
		rt_on_close(scene);
	else
		rt_switch_camera(scene);
	return (0);
}

void	rt_show_in_window(t_scene *s, const char *filename)
{
	t_camera	*camera;
	char		*header;

	header = ft_strjoin("miniRT - ", filename);
	if (header == NULL)
		rt_perror((void *)s, RT_SCENE);
	s->window = mlx_new_window(s->mlx, s->width, s->height, header);
	free(header);
	if (s->window == NULL)
		rt_xerror(s, RT_ERROR_XWINDOW, RT_ERROR_XWINDOW_MSG);
	mlx_clear_window(s->mlx, s->window);
	camera = s->active_camera->content;
	mlx_put_image_to_window(s->mlx, s->window, camera->viewport->img, 0, 0);
	mlx_hook(s->window, XEVENT_X, XMASK_X, rt_on_close, s);
	mlx_key_hook(s->window, rt_on_keypress, s);
	mlx_loop(s->mlx);
	rt_xerror(s, RT_ERROR_XLOOP, RT_ERROR_XLOOP_MSG);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc < 2 || argc > 3)
		rt_error(RT_ERROR_ARGS, RT_ERROR_ARGS_MSG RT_HELP);
	if (argc == 3 && ft_strcmp("--save", argv[2]))
		rt_error(RT_ERROR_ARGS, "Second argument must be --save" RT_HELP);
	scene = rt_init_scene(argc == 3);
	rt_load_scene(argv[1], &scene);
	rt_check_scene(&scene);
	rt_render_scene(&scene);
	if (scene.mlx == NULL)
		rt_save_to_bmp_files(&scene);
	else
		rt_show_in_window(&scene, argv[1]);
	return (0);
}
