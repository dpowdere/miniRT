/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:55:37 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 17:16:58 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdint.h>

# include <libft.h>

# include "rt_3d_objects.h"
# include "rt_errors.h"

# define UNDEFINED	-1

# ifdef __APPLE__
#  define RT_O_FLAGS	O_RDONLY | O_SYMLINK
# elif __linux__
#  define RT_O_FLAGS	O_RDONLY
# else
#  define RT_O_FLAGS	O_RDONLY
# endif

typedef struct	s_scene
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	float		ambient;
	t_color		ambient_color;
	t_list		*cameras;
	t_camera	*active_camera;
	t_list		*lights;
	t_list		*objects;
}				t_scene;

typedef struct	s_config_line
{
	char const			*line;
	char const *const	*segments;
	char const *const	*triplet;
	t_scene				*scene;
	size_t				line_num;
	size_t				n_segments;
}				t_config_line;

void			rt_config_line_regular_free(t_config_line *cline);
void			rt_config_line_emergency_free(t_config_line *cline);
int32_t			rt_get_color(int alpha, int red, int green, int blue);
void			rt_free_scene(t_scene *s);
t_scene			rt_init_scene(void);
void			rt_load_scene(const char *pathname, t_scene *scene);

void			rt_parse_config_line(const char *line, size_t lnum, t_scene *s);
void			rt_parse_triplet(t_config_line *c, int ix, const char *sname);
void			rt_parse_type(t_config_line *c);

t_color			rt_parse_color(t_config_line *c, int ix, const char *sname);
double			rt_parse_float(t_config_line *c, int ix, const char *sname);
t_vector		rt_parse_vector(t_config_line *c, int ix, const char *sname,
								int should_be_normalized);

void			rt_parse_ambient(t_config_line *cline);
void			rt_parse_camera(t_config_line *cline);
void			rt_parse_cylinder(t_config_line *cline);
void			rt_parse_light(t_config_line *cline);
void			rt_parse_plane(t_config_line *cline);
void			rt_parse_resolution(t_config_line *cline);
void			rt_parse_sphere(t_config_line *cline);
void			rt_parse_square(t_config_line *cline);
void			rt_parse_triangle(t_config_line *cline);

void			rt_error(int error_code, const char *error_msg);
void			rt_parsing_error(t_config_line *cline,
					const char *scope_name, const char *error_msg);
void			rt_perror(void *info, t_infotype infotype);
void			rt_scheme_error(void *info, t_infotype infotype,
						const char *scope_name, const char *error_msg);
void			rt_xerror(t_scene *s, int error_code, const char *error_msg);

#endif
