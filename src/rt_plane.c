/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:04:05 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:04:19 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_plane(t_config_line *c)
{
	t_plane	*pl;
	t_list	*list_element;

	if (c->n_segments != 4)
		rt_parsing_error(c, "Plane", "Wrong number of arguments");
	pl = (t_plane *)malloc(sizeof(t_plane));
	if (pl == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(int *)&pl->type = RT_PLANE;
	pl->origin = rt_parse_vector(c, 1, "Plane origin", NON_NORMALIZED);
	pl->orientation = rt_parse_vector(c, 2, "Plane orientation", NORMALIZED);
	pl->color = rt_parse_color(c, 3, "Plane color");
	list_element = ft_lstnew(pl);
	if (list_element == NULL)
	{
		free(pl);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}
