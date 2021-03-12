/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:42:48 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 13:08:43 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include <libft.h>

#include "minirt.h"

void	rt_config_line_regular_free(t_config_line *c)
{
	ft_free_null((void **)&c->segments);
	ft_free_null((void **)&c->triplet);
}

void	rt_config_line_emergency_free(t_config_line *c)
{
	rt_config_line_regular_free(c);
	ft_free_null((void **)&c->line);
	rt_free_scene(c->scene);
	c->scene = NULL;
}
