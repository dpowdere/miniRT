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

# include "rt_common.h"
# include "rt_3d_objects.h"
# include "rt_quadratic.h"
# include "rt_errors.h"

# ifndef DEBUG
#  define DEBUG	0
# endif

typedef struct s_scene
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_float		ambient;
	t_color		ambient_color;
	t_list		*cameras;
	t_list		*active_camera;
	t_list		*lights;
	t_list		*objects;
}			t_scene;

typedef struct s_config_line
{
	char const			*line;
	char const *const	*segments;
	char const *const	*triplet;
	t_scene				*scene;
	size_t				line_num;
	size_t				n_segments;
}			t_config_line;

void		rt_check_scene(t_scene *scene);
int32_t		rt_color_channels_to_int(int red, int green, int blue);
int32_t		rt_color_to_int(t_color c);
void		rt_config_line_regular_free(t_config_line *cline);
void		rt_config_line_emergency_free(t_config_line *cline);
void		rt_free_camera(void *camera);
void		rt_free_image(void *image);
void		rt_free_scene(t_scene *scene);
t_color		rt_init_color(int red, int green, int blue);
void		rt_init_camera_viewports(t_scene *scene);
t_image		*rt_init_image(t_scene *scene);
t_scene		rt_init_scene(int save);
void		rt_load_scene(const char *pathname, t_scene *scene);
void		rt_put_pixel(t_image *img, int x, int y, int color);
void		rt_render_scene(t_scene *scene);
void		rt_save_to_bmp_files(t_scene *scene);
void		rt_switch_camera(t_scene *scene);
void		rt_tweak_resolution(t_scene *scene);

t_color		rt_parse_color(t_config_line *c, int ix, const char *sname);
void		rt_parse_config_line(const char *line, size_t lnum, t_scene *s);
t_float		rt_parse_float(t_config_line *c, int ix, const char *sname);
void		rt_parse_triplet(t_config_line *c, int ix, const char *sname);
void		rt_parse_type(t_config_line *c);
t_vector	rt_parse_vector(t_config_line *c, int ix, const char *sname,
				int should_be_normalized);

void		rt_parse_ambient(t_config_line *cline);
void		rt_parse_camera(t_config_line *cline);
void		rt_parse_cylinder(t_config_line *cline);
void		rt_parse_light(t_config_line *cline);
void		rt_parse_plane(t_config_line *cline);
void		rt_parse_resolution(t_config_line *cline);
void		rt_parse_sphere(t_config_line *cline);
void		rt_parse_square(t_config_line *cline);
void		rt_parse_triangle(t_config_line *cline);

t_vector	vt_add(t_vector a, t_vector b);
t_scalar	vt_angle(t_vector v, t_vector w);
t_scalar	vt_distance(t_point p1, t_point p2);
t_vector	vt_init(t_float x, t_float y, t_float z);
int			vt_isequal(t_vector a, t_vector b);
int			vt_isinf(t_vector v);
t_vector	vt_inv(t_vector v);
t_scalar	vt_magnitude(t_vector v);
t_vector	vt_mul_cross(t_vector v, t_vector w);
t_scalar	vt_mul_dot(t_vector v, t_vector w);
t_vector	vt_mul_sc(t_vector v, t_scalar k);
t_vector	vt_normalize(t_vector v);
t_float		vt_rad(t_float deg);

t_color		rt_get_color(t_x intersection, t_scene *scene);
t_x			rt_get_intersection(t_ray ray, void *obj);
t_x			rt_get_nearest_intersection(t_x x1, t_x x2);
t_x			rt_get_no_intersection(t_ray ray, void *obj);
t_x			rt_sphere_intersection(t_ray ray, t_sphere *sp);
t_vector	rt_sphere_normal(t_x x);

void		rt_error(int error_code, const char *error_msg);
void		rt_parsing_error(t_config_line *cline,
				const char *scope_name, const char *error_msg);
void		rt_perror(void *info, t_infotype infotype);
void		rt_scheme_error(void *info, t_infotype infotype,
				const char *scope_name, const char *error_msg);
void		rt_xerror(t_scene *s, int error_code, const char *error_msg);

# ifdef __APPLE__
#  define RT_O_RDONLY			O_RDONLY | O_SYMLINK
#  define DESTROY_XDISPLAY(x)	NULL
# elif __linux__
#  define RT_O_RDONLY			O_RDONLY
#  define DESTROY_XDISPLAY(x)	mlx_destroy_display(x)
# else
#  define RT_O_RDONLY			O_RDONLY
#  define DESTROY_XDISPLAY(x)	NULL
# endif

# define UNDEFINED	-1

#endif
