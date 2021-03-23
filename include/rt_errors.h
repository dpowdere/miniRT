/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:08:56 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 17:09:49 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# define RT_ERROR_SYSTEM		1

# define RT_ERROR_ARGS			2
# define RT_ERROR_XLOOP			3
# define RT_ERROR_XSERVER		4
# define RT_ERROR_XWINDOW		5
# define RT_ERROR_LINEREAD		6
# define RT_ERROR_NO_RTFILE		7
# define RT_ERROR_PARSE			8
# define RT_ERROR_SCHEME		9
# define RT_ERROR_XIMAGE		10

# define RT_ERROR_ARGS_MSG		"Invalid number of arguments"
# define RT_ERROR_XLOOP_MSG		"Can't enter the main loop"
# define RT_ERROR_XSERVER_MSG	"Can't establish connection with display server"
# define RT_ERROR_XWINDOW_MSG	"Can't display a window"
# define RT_ERROR_LINEREAD_MSG	"Can't read a line from the scene config file"
# define RT_ERROR_NO_RTFILE_MSG	"Can parse *.rt files only"
# define RT_ERROR_PARSE_MSG		"Can't parse the scene config file"
# define RT_ERROR_SCHEME_MSG	"Scene config does not comply with the scheme"
# define RT_ERROR_XIMAGE_MSG	"Can't create an image buffer"

typedef const enum	e_infotype
{
	RT_SCENE,
	RT_CONFIG_LINE
}					t_infotype;

#endif
