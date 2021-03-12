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
** stddef.h - NULL
** stdlib.h - free
** unistd.h - close
*/

#include <mlx.h>
#include <libft.h>

#include "minirt.h"

t_scene	rt_init_scene(void)
{
	t_scene scene;

	scene.mlx = NULL;
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
	if (scene->mlx != NULL)
	{
		mlx_destroy_display(scene->mlx);
		scene->mlx = NULL;
	}
	scene->active_camera = NULL;
	ft_lstclear(&scene->cameras, free);
	ft_lstclear(&scene->lights, free);
	ft_lstclear(&scene->objects, free);
}

void	rt_read_scene(int fd, t_scene *scene)
{
	char	*line;
	size_t	line_num;
	int		retcode;

	line = NULL;
	line_num = 0;
	while ((retcode = ft_get_next_line(fd, &line)) > 0)
	{
		rt_parse_line(line, ++line_num, scene);
		free(line);
		line = NULL;
	}
	if (retcode < 0)
		rt_xerror(scene, RT_ERROR_LINEREAD, RT_ERROR_LINEREAD_MSG);
}

void	rt_load_scene(const char *pathname, t_scene *scene)
{
	int	fd;

	if (!ft_str_endswith(pathname, ".rt"))
		rt_error(RT_ERROR_NORTFILE, RT_ERROR_NORTFILE_MSG);
	if ((fd = open(pathname, RT_O_FLAGS)) == -1)
		rt_perror(scene);
	rt_read_scene(fd, scene);
	if (close(fd) == -1)
		rt_perror(scene);
	//rt_check_scene(scene);
}
