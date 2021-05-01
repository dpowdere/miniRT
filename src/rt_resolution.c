/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:04:59 by dpowdere          #+#    #+#             */
/*   Updated: 2021/05/01 20:05:29 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include <mlx.h>
#include <libft.h>

#include "minirt.h"

#define BASE	10
#define SCREEN_HEADER_HEIGHT	100

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

int	rt_tweak_resolution(t_scene *scene)
{
	int	resolution_changed;
	int	screen_width;
	int	screen_height;
	int	ret;

	screen_width = 8192;
	screen_height = 8192 + SCREEN_HEADER_HEIGHT;
	resolution_changed = FALSE;
	if (scene->mlx)
	{
		ret = mlx_get_screen_size(scene->mlx, &screen_width, &screen_height);
		if ((ret && ON_MACOS) || (!ret && ON_LINUX))
			rt_xerror(scene, RT_ERROR_XSERVER, RT_ERROR_XSERVER_MSG);
	}
	if (scene->width > screen_width)
	{
		scene->width = screen_width;
		resolution_changed = TRUE;
	}
	if (scene->height > screen_height - SCREEN_HEADER_HEIGHT)
	{
		scene->height = screen_height - SCREEN_HEADER_HEIGHT;
		resolution_changed = TRUE;
	}
	return (resolution_changed);
}
