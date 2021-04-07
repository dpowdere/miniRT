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
	FT_EPRINTLN("Error");
	FT_EPRINTLN(error_msg);
	exit(error_code);
}

void	rt_xerror(t_scene *s, int error_code, const char *error_msg)
{
	rt_free_scene(s);
	rt_error(error_code, error_msg);
}

void	rt_perror(void *info, t_infotype infotype)
{
	if (infotype == RT_SCENE)
		rt_free_scene((t_scene *)info);
	else if (infotype == RT_CONFIG_LINE)
		rt_config_line_emergency_free((t_config_line *)info);
	FT_EPRINTLN("Error");
	perror(NULL);
	exit(RT_ERROR_SYSTEM);
}

void	rt_parsing_error(t_config_line *cline, const char *scope_name,
							const char *error_msg)
{
	char *line_num;

	line_num = ft_itoa(cline->line_num);
	rt_config_line_emergency_free(cline);
	FT_EPRINTLN("Error");
	FT_EPRINT(RT_ERROR_PARSE_MSG ", line ");
	FT_EPRINTLN(line_num);
	free(line_num);
	if (scope_name != NULL)
	{
		FT_EPRINT(scope_name);
		FT_EPRINT(": ");
	}
	if (error_msg != NULL)
		FT_EPRINTLN(error_msg);
	else
		FT_EPRINT("\n");
	exit(RT_ERROR_PARSE);
}

void	rt_scheme_error(void *info, t_infotype infotype,
						const char *scope_name, const char *error_msg)
{
	char			*line_num;

	FT_EPRINTLN("Error");
	FT_EPRINT(RT_ERROR_SCHEME_MSG);
	if (infotype == RT_SCENE)
		rt_free_scene((t_scene *)info);
	else if (infotype == RT_CONFIG_LINE)
	{
		line_num = ft_itoa(((t_config_line *)info)->line_num);
		rt_config_line_emergency_free((t_config_line *)info);
		FT_EPRINT(", line ");
		FT_EPRINT(line_num);
		free(line_num);
	}
	FT_EPRINT("\n");
	if (scope_name != NULL)
	{
		FT_EPRINT(scope_name);
		FT_EPRINT(": ");
	}
	if (error_msg != NULL)
		FT_EPRINTLN(error_msg);
	else
		FT_EPRINT("\n");
	exit(RT_ERROR_SCHEME);
}
