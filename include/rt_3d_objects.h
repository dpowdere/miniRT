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

# define BITS_PER_PIXEL		24
# define BYTES_PER_PIXEL	3

typedef struct		s_color
{
	int red;
	int green;
	int blue;
}					t_color;

typedef struct		s_vector
{
	double x;
	double y;
	double z;
}					t_vector;

# define NORMALIZED		1
# define NON_NORMALIZED	0

typedef const enum	e_objtype
{
	RT_CYLINDER,
	RT_PLANE,
	RT_SPHERE,
	RT_SQUARE,
	RT_TRIANGLE,
}					t_objtype;

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
	double		view_angle;
	t_image		*viewport;
}					t_camera;

typedef struct		s_light
{
	t_vector	location;
	double		intensity;
	t_color		color;
}					t_light;

typedef struct		s_cylinder
{
	t_objtype	type;
	t_vector	location;
	t_vector	orientation;
	double		diameter;
	double		height;
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
	double		diameter;
	t_color		color;
}					t_sphere;

typedef struct		s_square
{
	t_objtype	type;
	t_vector	location;
	t_vector	orientation;
	double		side_size;
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

#endif
