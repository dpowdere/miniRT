/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:02:56 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:03:08 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

#define NM "Light"

void	rt_parse_light(t_config_line *c)
{
	t_light	*light;
	t_list	*list_element;

	if (c->n_segments != 4)
		rt_parsing_error(c, NM, "Wrong number of arguments");
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	light->origin = rt_parse_vector(c, 1, NM " origin", NON_NORMALIZED);
	light->intensity = rt_parse_float(c, 2, NM " intensity");
	if (light->intensity < 0.0 || light->intensity > 1.0)
		rt_scheme_error(c, RT_CONFIG_LINE,
			NM, "Intensity must be in the range [0, 1.0]");
	light->color = rt_parse_color(c, 3, NM " color");
	list_element = ft_lstnew(light);
	if (list_element == NULL)
	{
		free(light);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->lights, list_element);
}
