/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:04:59 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/15 17:00:33 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include <mlx.h>
#include <libft.h>

#include "minirt.h"

#define BASE 10

void	rt_parse_resolution(t_config_line *c)
{
	int		width;
	int		height;
	char	*endptr;

	if (c->scene->width != UNDEFINED || c->scene->height != UNDEFINED)
		rt_scheme_error(c, RT_CONFIG_LINE,
			"Resolution", "Can be specified only once");
	if (c->n_segments != 3)
		rt_parsing_error(c, "Resolution", "Wrong number of arguments");
	endptr = NULL;
	width = ft_strtoi(c->segments[1], &endptr, BASE);
	if (*endptr != '\0' || width < 1)
		rt_parsing_error(c, "Resolution width", "Invalid value");
	c->scene->width = width;
	height = ft_strtoi(c->segments[2], &endptr, BASE);
	if (*endptr != '\0' || height < 1)
		rt_parsing_error(c, "Resolution height", "Invalid value");
	c->scene->height = height;
}

void	rt_tweak_resolution(t_scene *scene)
{
	int	screen_width;
	int	screen_height;

	screen_width = 8192;
	screen_height = 8192;
	if (scene->mlx)
		if (mlx_get_screen_size(scene->mlx, &screen_width, &screen_height))
			rt_xerror(scene, RT_ERROR_XSERVER, RT_ERROR_XSERVER_MSG);
	if (scene->width > screen_width)
		scene->width = screen_width;
	if (scene->height > screen_height)
		scene->height = screen_height;
}
