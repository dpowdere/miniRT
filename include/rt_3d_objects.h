/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_3d_objects.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:06:42 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 17:11:59 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_3D_OBJECTS_H
# define RT_3D_OBJECTS_H

# include "rt_common.h"

# define BITS_PER_PIXEL		24
# define BYTES_PER_PIXEL	3

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}						t_color;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}						t_point;

typedef t_point			t_vector;
typedef double			t_scalar;

# define NON_NORMALIZED	0
# define NORMALIZED		1

typedef struct s_ray
{
	t_point		origin;
	t_vector	orientation;
}						t_ray;

typedef enum e_otype
{
	RT_CYLINDER = 1,
	RT_PLANE,
	RT_SPHERE,
	RT_SQUARE,
	RT_TRIANGLE,
}						t_otype;
typedef const t_otype	t_objtype;

# define NUM_DENSE_OBJECTS	5

typedef struct s_scene	t_scene;
typedef struct s_image
{
	void	*img;
	char	*byte_array;
	int		bytes_per_pixel;
	int		bytes_per_line;
	int		switch_endianness;
	t_scene	*scene;
}						t_image;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	x_ornt;
	t_vector	y_ornt;
	t_vector	z_ornt;
	double		view_angle;
	t_image		*viewport;
	double		width;
	double		height;
}						t_camera;

typedef struct s_light
{
	t_vector	origin;
	double		intensity;
	t_color		color;
}						t_light;

typedef struct s_object
{
	t_objtype	type;
}						t_object;

typedef struct s_cylinder
{
	t_objtype	type;
	t_vector	origin;
	t_vector	orientation;
	double		diameter;
	double		height;
	t_color		color;
}						t_cylinder;

typedef struct s_plane
{
	t_objtype	type;
	t_vector	origin;
	t_vector	orientation;
	t_color		color;
}						t_plane;

typedef struct s_sphere
{
	t_objtype	type;
	t_vector	origin;
	double		radius;
	t_color		color;
}						t_sphere;

typedef struct s_square
{
	t_objtype	type;
	t_vector	origin;
	t_vector	orientation;
	double		side_size;
	t_color		color;
}						t_square;

typedef struct s_triangle
{
	t_objtype	type;
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
	t_color		color;
}						t_triangle;

typedef struct s_intersection
{
	void		*object;
	t_ray		ray;
	t_point		point;
	t_vector	normal;
	int			is_flip_side;
	t_color		color;
}						t_x;

#endif
