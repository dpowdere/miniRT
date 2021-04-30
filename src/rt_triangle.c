/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:07:34 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:07:46 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_triangle(t_config_line *c)
{
	t_triangle	*tr;
	t_list		*list_element;

	if (c->n_segments != 5)
		rt_parsing_error(c, "Triangle", "Wrong number of arguments");
	tr = (t_triangle *)malloc(sizeof(t_triangle));
	if (tr == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(t_otype *)&tr->type = RT_TRIANGLE;
	tr->p1 = rt_parse_vector(c, 1, "Triangle, point 1", NON_NORMALIZED);
	tr->p2 = rt_parse_vector(c, 2, "Triangle, point 2", NON_NORMALIZED);
	tr->p3 = rt_parse_vector(c, 3, "Triangle, point 3", NON_NORMALIZED);
	tr->color = rt_parse_color(c, 4, "Triangle color");
	list_element = ft_lstnew(tr);
	if (list_element == NULL)
	{
		free(tr);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}
