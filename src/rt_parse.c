/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 23:48:40 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/11 23:50:38 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include <libft.h>

#include "minirt.h"

#define SPACES	" \f\n\r\t\v"

void	rt_parse_line(const char *line, t_scene *scene)
{
	char *const	*parts;
	size_t		len;
	int			i;

	(void)scene;
	i = 0;
	parts = ft_split_const(line, SPACES);
	len = ft_ptrarr_len((void **)parts);
	if (len > 0)
	{
		printf(">>>");
		while (parts[i])
		{
			printf(" %s", parts[i]);
			++i;
		}
		printf("\n");
	}
	free((void *)parts);
}
