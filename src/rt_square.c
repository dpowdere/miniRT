/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:06:47 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 02:07:09 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

void	rt_parse_square(t_config_line *c)
{
	t_square	*sq;
	t_list		*list_element;

	if (c->n_segments != 5)
		rt_parsing_error(c, "Square", "Wrong number of arguments");
	sq = (t_square *)malloc(sizeof(t_square));
	if (sq == NULL)
		rt_perror((void *)c, RT_CONFIG_LINE);
	*(int *)&sq->type = RT_SQUARE;
	sq->origin = rt_parse_vector(c, 1, "Square origin", NON_NORMALIZED);
	sq->orientation = rt_parse_vector(c, 2, "Square orientation", NORMALIZED);
	sq->side_size = rt_parse_float(c, 3, "Square side size");
	sq->color = rt_parse_color(c, 4, "Square color");
	list_element = ft_lstnew(sq);
	if (list_element == NULL)
	{
		free(sq);
		rt_perror((void *)c, RT_CONFIG_LINE);
	}
	ft_lstadd_back(&c->scene->objects, list_element);
}
