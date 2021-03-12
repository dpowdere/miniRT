/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:58:04 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/11 19:02:25 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*
** stddef.h - NULL
** stdio.h  - perror
** stdlib.h - exit
*/

#include <libft.h>

#include "minirt.h"

void	rt_error(int error_code, const char *error_msg)
{
	ft_eprintln("Error");
	ft_eprintln(error_msg);
	exit(error_code);
}

void	rt_perror(void)
{
	ft_eprintln("Error");
	perror(NULL);
	exit(RT_ERROR_SYSTEM);
}

void	rt_parse_error(t_config_line *cline, const char *error_msg)
{
	char *line_num;

	line_num = ft_itoa(cline->line_num);
	ft_eprintln("Error");
	ft_eprint(RT_ERROR_PARSE_MSG ", line ");
	ft_eprintln(line_num);
	free(line_num);
	ft_eprintln(error_msg);
	exit(RT_ERROR_PARSE);
}
