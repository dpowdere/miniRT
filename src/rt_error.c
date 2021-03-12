/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:58:04 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 12:44:44 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <libft.h>

#include "minirt.h"

#define DO_NOT_FREE_ERROR_MSG 0

/*
** stddef.h - NULL
** stdio.h  - perror
** stdlib.h - exit
*/

void	rt_error(int error_code, const char *error_msg)
{
	ft_eprintln("Error");
	ft_eprintln(error_msg);
	exit(error_code);
}

void	rt_xerror(t_scene *s, int error_code, const char *error_msg)
{
	rt_free_scene(s);
	rt_error(error_code, error_msg);
}

void	rt_perror(t_scene *s)
{
	rt_free_scene(s);
	ft_eprintln("Error");
	perror(NULL);
	exit(RT_ERROR_SYSTEM);
}

void	rt_parsing_error(t_config_line *cline, const char *scope_name,
							const char *error_msg)
{
	char *line_num;

	line_num = ft_itoa(cline->line_num);
	rt_config_line_emergency_free(cline);
	ft_eprintln("Error");
	ft_eprint(RT_ERROR_PARSE_MSG ", line ");
	ft_eprintln(line_num);
	free(line_num);
	if (scope_name != NULL)
	{
		ft_eprint(scope_name);
		ft_eprint(": ");
	}
	if (error_msg != NULL)
		ft_eprintln(error_msg);
	else
		ft_eprint("\n");
	exit(RT_ERROR_PARSE);
}
