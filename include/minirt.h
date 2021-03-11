/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:55:37 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/11 19:03:15 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdint.h>
# include "rt_keys.h"

# define UNDEFINED	-1

# define RT_ERROR_SYSTEM		1

# define RT_ERROR_ARGS			2
# define RT_ERROR_XLOOP			3
# define RT_ERROR_XSERVER		4
# define RT_ERROR_XWINDOW		5
# define RT_ERROR_LINEREAD		6
# define RT_ERROR_NORTFILE		7
# define RT_ERROR_PARSE_UNKNOWN	8

# define RT_ERROR_ARGS_MSG		"Invalid arguments"
# define RT_ERROR_XLOOP_MSG		"Can't enter the main loop"
# define RT_ERROR_XSERVER_MSG	"Can't establish connection with display server"
# define RT_ERROR_XWINDOW_MSG	"Can't display a window"
# define RT_ERROR_LINEREAD_MSG	"Reading lines of the file failed"
# define RT_ERROR_NORTFILE_MSG	"Can parse *.rt files only"
# define RT_ERROR_PARSE_UNKNOWN_MSG	"Unknown element in the scene config file"

# ifdef __APPLE__
#  define RT_O_FLAGS	O_RDONLY | O_SYMLINK
# elif __linux__
#  define RT_O_FLAGS	O_RDONLY
# else
#  define RT_O_FLAGS	O_RDONLY
# endif

typedef struct	s_scene
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}				t_scene;

void			rt_error(int error_code, char *error_msg);
int32_t			rt_get_color(int alpha, int red, int green, int blue);
t_scene			rt_init_scene(void);
void			rt_load_scene(const char *pathname, t_scene *scene);
void			rt_parse_line(const char *line, t_scene *scene);
void			rt_perror(void);

void			rt_parse_ambient(char *const *segs, size_t n, t_scene *s);
void			rt_parse_camera(char *const *segs, size_t n, t_scene *s);
void			rt_parse_cylinder(char *const *segs, size_t n, t_scene *s);
void			rt_parse_light(char *const *segs, size_t n, t_scene *s);
void			rt_parse_plane(char *const *segs, size_t n, t_scene *s);
void			rt_parse_resolution(char *const *segs, size_t n, t_scene *s);
void			rt_parse_sphere(char *const *segs, size_t n, t_scene *s);
void			rt_parse_square(char *const *segs, size_t n, t_scene *s);
void			rt_parse_triangle(char *const *segs, size_t n, t_scene *s);

#endif
