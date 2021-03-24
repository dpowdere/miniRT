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

t_image	*rt_init_image(t_scene *s)
{
	t_image	*image;
	int		bits_per_pixel;
	int		is_big_endian;

	if ((image = malloc(sizeof(t_image))) == NULL)
		rt_xerror(s, RT_ERROR_XIMAGE, RT_ERROR_XIMAGE_MSG);
	if ((image->img = mlx_new_image(s->mlx, s->width, s->height)) == NULL)
		rt_xerror(s, RT_ERROR_XIMAGE, RT_ERROR_XIMAGE_MSG);
	image->byte_array = mlx_get_data_addr(image->img, &bits_per_pixel,
			&image->bytes_per_line, &is_big_endian);
	image->switch_endianness = is_big_endian != ft_is_big_endian();
	image->bytes_per_pixel = bits_per_pixel / 8 + (bits_per_pixel % 8 > 0);
	image->scene = s;
	return (image);
}

void	rt_free_image(void *img)
{
	void	*mlx_ptr;
	void	*img_ptr;
	t_image	*image;

	image = (t_image *)img;
	mlx_ptr = image->scene->mlx;
	img_ptr = image->img;
	image->byte_array = NULL;
	image->img = NULL;
	image->scene = NULL;
	mlx_destroy_image(mlx_ptr, img_ptr);
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
	prepared_color = mlx_get_color_value(img->scene->mlx, color);
	px = img->byte_array + y * img->bytes_per_line + x * img->bytes_per_pixel;
	while (++i < img->bytes_per_pixel)
		px[a + i * b] = *((char *)&prepared_color + i);
}
