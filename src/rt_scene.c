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
#include <stdlib.h>
#include <unistd.h>

/*
** fcntl.h  - open
** stddef.h - NULL
** stdlib.h - free
** unistd.h - close
*/

#include <libft.h>

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
		rt_error(RT_ERROR_LINEREAD, RT_ERROR_LINEREAD_MSG);
}

void	rt_load_scene(const char *pathname, t_scene *scene)
{
	int	fd;

	if (!ft_str_endswith(pathname, ".rt"))
		rt_error(RT_ERROR_NORTFILE, RT_ERROR_NORTFILE_MSG);
	if ((fd = open(pathname, RT_O_FLAGS)) == -1)
		rt_perror();
	rt_read_scene(fd, scene);
	if (close(fd) == -1)
		rt_perror();
	//rt_check_scene(scene);
}
