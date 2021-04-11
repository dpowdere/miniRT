/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:22:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/11 18:38:43 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/*
** fcntl.h  - open
** math.h   - NAN
** stddef.h - NULL
** stdlib.h - free
** unistd.h - close
*/

#include <mlx.h>
#include <libft.h>

#include "minirt.h"

t_scene	rt_init_scene(int save)
{
	t_scene	scene;

	scene.mlx = NULL;
	if (!save)
	{
		scene.mlx = mlx_init();
		if (scene.mlx == NULL)
			rt_error(RT_ERROR_XSERVER, RT_ERROR_XSERVER_MSG);
	}
	scene.window = NULL;
	scene.width = UNDEFINED;
	scene.height = UNDEFINED;
	scene.ambient = NAN;
	scene.ambient_color.red = UNDEFINED;
	scene.ambient_color.green = UNDEFINED;
	scene.ambient_color.blue = UNDEFINED;
	scene.cameras = NULL;
	scene.active_camera = NULL;
	scene.lights = NULL;
	scene.objects = NULL;
	return (scene);
}

void	rt_free_scene(t_scene *scene)
{
	if (scene->mlx != NULL && scene->window != NULL)
	{
		mlx_destroy_window(scene->mlx, scene->window);
		scene->window = NULL;
	}
	scene->active_camera = NULL;
	ft_lstclear(&scene->cameras, rt_free_camera);
	ft_lstclear(&scene->lights, free);
	ft_lstclear(&scene->objects, free);
	if (scene->mlx != NULL)
	{
		DESTROY_XDISPLAY(scene->mlx);
		scene->mlx = NULL;
	}
}

void	rt_read_scene(int fd, t_scene *scene)
{
	char	*line;
	size_t	line_num;
	int		retcode;

	line = NULL;
	line_num = 0;
	retcode = ft_get_next_line(fd, &line);
	while (retcode > 0)
	{
		rt_parse_config_line(line, ++line_num, scene);
		free(line);
		line = NULL;
		retcode = ft_get_next_line(fd, &line);
	}
	if (retcode < 0)
		rt_xerror(scene, RT_ERROR_LINEREAD, RT_ERROR_LINEREAD_MSG);
}

void	rt_check_scene(t_scene *scene)
{
	if (scene->width == UNDEFINED || scene->height == UNDEFINED)
		rt_scheme_error(scene, RT_SCENE, NULL, "No resolution is specified");
	if (isnan(scene->ambient))
		rt_scheme_error(scene, RT_SCENE, NULL,
			"No abmbient lighting is specified");
	if (scene->cameras == NULL)
		rt_scheme_error(scene, RT_SCENE, NULL, "No camera is specified");
	if (scene->objects == NULL)
		rt_scheme_error(scene, RT_SCENE, NULL,
			"There is no geometric object in the scene");
	rt_tweak_resolution(scene);
	rt_init_camera_viewports(scene);
}

void	rt_load_scene(const char *pathname, t_scene *scene)
{
	int	fd;

	if (!ft_str_endswith(pathname, ".rt"))
		rt_error(RT_ERROR_NO_RTFILE, RT_ERROR_NO_RTFILE_MSG);
	fd = open(pathname, RT_O_RDONLY);
	if (fd == -1)
		rt_perror((void *)scene, RT_SCENE);
	rt_read_scene(fd, scene);
	if (close(fd) == -1)
		rt_perror((void *)scene, RT_SCENE);
}
