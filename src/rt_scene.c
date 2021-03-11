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
#include <stddef.h>
#include <unistd.h>

/*
** fcntl.h  - open
** unistd.h - close
** stddef.h - NULL
*/

#include "minirt.h"

t_scene	rt_init_scene(void)
{
	t_scene scene;

	scene.mlx = NULL;
	scene.window = NULL;
	scene.width = UNDEFINED;
	scene.height = UNDEFINED;
	return (scene);
}

void	rt_load_scene(const char *pathname, t_scene *scene)
{
	int	fd;

	(void)scene;
	if ((fd = open(pathname, RT_O_FLAGS)) == -1)
		rt_perror();
	if (close(fd) == -1)
		rt_perror();
}
