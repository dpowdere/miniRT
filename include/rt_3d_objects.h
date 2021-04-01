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

typedef struct		s_color
{
	int red;
	int green;
	int blue;
}					t_color;

typedef struct		s_point
{
	t_float x;
	t_float y;
	t_float z;
}					t_point;

typedef t_point		t_vector;
typedef t_float		t_scalar;

# define NORMALIZED		1
# define NON_NORMALIZED	0

typedef enum		e_otype
{
	RT_CYLINDER,
	RT_PLANE,
	RT_SPHERE,
	RT_SQUARE,
	RT_TRIANGLE,
}					t_otype;
typedef const t_otype	t_objtype;

# define NUM_DENSE_OBJECTS	5

typedef struct s_scene	t_scene;
typedef struct		s_image
{
	void	*img;
	char	*byte_array;
	int		bytes_per_pixel;
	int		bytes_per_line;
	int		switch_endianness;
	t_scene	*scene;
}					t_image;

typedef struct		s_camera
{
	t_vector	location;
	t_vector	orientation;
	t_float		view_angle;
	t_image		*viewport;
}					t_camera;

typedef struct		s_light
{
	t_vector	location;
	t_float		intensity;
	t_color		color;
}					t_light;

typedef struct		s_object
{
	t_objtype	type;
}					t_object;

typedef struct		s_cylinder
{
	t_objtype	type;
	t_vector	location;
	t_vector	orientation;
	t_float		diameter;
	t_float		height;
	t_color		color;
}					t_cylinder;

typedef struct		s_plane
{
	t_objtype	type;
	t_vector	location;
	t_vector	orientation;
	t_color		color;
}					t_plane;

typedef struct		s_sphere
{
	t_objtype	type;
	t_vector	location;
	t_float		diameter;
	t_color		color;
}					t_sphere;

typedef struct		s_square
{
	t_objtype	type;
	t_vector	location;
	t_vector	orientation;
	t_float		side_size;
	t_color		color;
}					t_square;

typedef struct		s_triangle
{
	t_objtype	type;
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
	t_color		color;
}					t_triangle;

typedef struct		s_intersection
{
	void		*object;
	t_point		point;
}					t_x;

typedef t_x			(*t_xfunc)();
typedef t_color		(*t_cfunc)();

#endif
