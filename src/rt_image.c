/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:27:22 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/23 19:29:42 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

#include <mlx.h>
#include <libft.h>

#include "minirt.h"
#include "rt_bmp.h"

t_image	*rt_init_dib(t_scene *s)
{
	t_image	*image;
	int		bytes_per_line;
	int		antipad;

	if ((image = malloc(sizeof(t_image))) == NULL)
		rt_perror(s, RT_SCENE);
	image->img = NULL;
	bytes_per_line = BYTES_PER_PIXEL * s->width;
	antipad = bytes_per_line % DIB_BYTE_FACTOR;
	bytes_per_line += DIB_BYTE_FACTOR * (antipad > 0) - antipad;
	if ((image->byte_array = malloc(bytes_per_line * s->height)) == NULL)
	{
		free(image);
		rt_perror(s, RT_SCENE);
	}
	image->bytes_per_line = bytes_per_line;
	image->switch_endianness = ft_is_big_endian();
	image->bytes_per_pixel = BYTES_PER_PIXEL;
	image->scene = s;
	return (image);
}

t_image	*rt_init_image(t_scene *s)
{
	t_image	*image;
	int		bits_per_pixel;
	int		is_big_endian;

	if (s->mlx == NULL)
		return (rt_init_dib(s));
	if ((image = malloc(sizeof(t_image))) == NULL)
		rt_perror(s, RT_SCENE);
	if ((image->img = mlx_new_image(s->mlx, s->width, s->height)) == NULL)
	{
		free(image);
		rt_xerror(s, RT_ERROR_XIMAGE, RT_ERROR_XIMAGE_MSG);
	}
	image->byte_array = mlx_get_data_addr(image->img, &bits_per_pixel,
			&image->bytes_per_line, &is_big_endian);
	ft_memset(image->byte_array, 0, image->bytes_per_line * s->height);
	image->switch_endianness = is_big_endian != ft_is_big_endian();
	image->bytes_per_pixel = bits_per_pixel / 8 + (bits_per_pixel % 8 > 0);
	image->scene = s;
	return (image);
}

void	rt_free_image(void *img)
{
	t_image	*image;
	void	*mlx_ptr;
	void	*img_ptr;

	if (img == NULL)
		return ;
	image = (t_image *)img;
	if (image->scene->mlx != NULL)
	{
		mlx_ptr = image->scene->mlx;
		img_ptr = image->img;
		image->byte_array = NULL;
		mlx_destroy_image(mlx_ptr, img_ptr);
	}
	else
	{
		if (image->byte_array != NULL)
			free(image->byte_array);
		image->byte_array = NULL;
	}
	image->img = NULL;
	image->scene = NULL;
	free(img);
}

void	rt_put_pixel(t_image *img, int x, int y, int color)
{
	char	*px;
	int		prepared_color;
	int		i;
	int		a;
	int		b;

	i = -1;
	a = 0;
	b = 1;
	if (img->switch_endianness)
	{
		a = img->bytes_per_pixel - 1;
		b = -1;
	}
	prepared_color = color;
	if (img->scene->mlx != NULL)
		prepared_color = mlx_get_color_value(img->scene->mlx, color);
	px = img->byte_array + y * img->bytes_per_line + x * img->bytes_per_pixel;
	while (++i < img->bytes_per_pixel)
		px[a + i * b] = *((char *)&prepared_color + i);
}
