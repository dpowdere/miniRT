/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_config_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:49:02 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/22 21:49:55 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

#include <libft.h>

#include "minirt.h"

#define SPACES	" \f\n\r\t\v"

void	rt_parse_config_line(const char *line, size_t line_num, t_scene *scene)
{
	t_config_line	config_line;
	int				i;

	i = 0;
	config_line.line = line;
	config_line.line_num = line_num;
	config_line.segments = (char const *const *)ft_split_const(line, SPACES);
	config_line.n_segments = ft_ptrarr_len((void **)config_line.segments);
	config_line.triplet = NULL;
	config_line.scene = scene;
	if (config_line.n_segments > 0)
	{
		if (DEBUG)
		{
			printf(">>>");
			while (config_line.segments[i])
			{
				printf(" %s", config_line.segments[i]);
				++i;
			}
			printf("\n");
		}
		rt_parse_type(&config_line);
	}
	rt_config_line_regular_free(&config_line);
}
