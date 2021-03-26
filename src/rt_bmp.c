/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:20:23 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/24 16:21:46 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/*
** errno.h  - EEXIST
** fcntl.h  - open
** stddef.h - NULL, size_t
** stdint.h - int16_t, uint16_t, uint32_t
** stdlib.h - free, malloc
** unistd.h - close
*/

#include <libft.h>

#include "minirt.h"
#include "rt_bmp.h"

#define FILEPREFIX		"view_"
#define FILEPATH_LEN	20

/*
** Populating the DIB header in the BITMAPCOREHEADER format.
*/

void	rt_dib_bitmapcoreheader(char *mem, t_scene *scene)
{
	*(uint32_t *)(mem + SH_DIB_CR_SIZE) = BITMAPCOREHEADER_SIZE;
	*(uint16_t *)(mem + SH_DIB_CR_WIDTH) = scene->width;
	*(int16_t *)(mem + SH_DIB_CR_HEIGHT) = -scene->height;
	*(uint16_t *)(mem + SH_DIB_CR_PLANES) = 1;
	*(uint16_t *)(mem + SH_DIB_CR_BPP) = BITS_PER_PIXEL;
}

/*
** Populating the DIB header in the BITMAPINFOHEADER format.
*/

void	rt_dib_bitmapinfoheader(char *mem, t_scene *scene)
{
	*(uint32_t *)(mem + SH_DIB_NF_SIZE) = DIB_HEADER_SIZE;
	*(int32_t *)(mem + SH_DIB_NF_WIDTH) = scene->width;
	*(int32_t *)(mem + SH_DIB_NF_HEIGHT) = -scene->height;
	*(uint16_t *)(mem + SH_DIB_NF_PLANES) = 1;
	*(uint16_t *)(mem + SH_DIB_NF_BPP) = BITS_PER_PIXEL;
	*(uint32_t *)(mem + SH_DIB_NF_COMPRESSION) = DIB_COMPRESSION_RGB;
	*(uint32_t *)(mem + SH_DIB_NF_IMAGE_SIZE) =
				((t_camera *)scene->cameras->content)
					->viewport->bytes_per_line * scene->height;
	*(uint32_t *)(mem + SH_DIB_NF_XPPM) = PIXELS_PER_METER;
	*(uint32_t *)(mem + SH_DIB_NF_YPPM) = PIXELS_PER_METER;
	*(uint32_t *)(mem + SH_DIB_NF_USED_COLORS) = DIB_ALL_COLORS_ARE_USED;
	*(uint32_t *)(mem + SH_DIB_NF_IMPT_COLORS) = DIB_ALL_COLORS_ARE_IMPORTANT;
}

char	*rt_init_header(t_scene *scene)
{
	char	*mem;
	size_t	file_size;

	if ((mem = malloc(BMP_HEADER_SIZE + DIB_HEADER_SIZE)) == NULL)
		rt_perror(scene, RT_SCENE);
	ft_memcpy(mem + SH_BMP_TYPE, "BM", 2);
	file_size = BMP_HEADER_SIZE + DIB_HEADER_SIZE +
				((t_camera *)scene->cameras->content)
					->viewport->bytes_per_line * scene->height;
	*(uint32_t *)(mem + SH_BMP_FILESIZE) = file_size;
	*(uint32_t *)(mem + SH_BMP_RESERVED) = 0;
	*(uint32_t *)(mem + SH_BMP_DATAOFFSET) = BMP_HEADER_SIZE + DIB_HEADER_SIZE;
	rt_dib_bitmapinfoheader(mem, scene);
	return (mem);
}

int		rt_open_bmp_file(int *serial_number, t_scene *scene)
{
	extern int	errno;
	char		*number;
	char		filepath[FILEPATH_LEN];
	int			fd;

	while (1)
	{
		ft_memset(filepath, 0, FILEPATH_LEN);
		ft_strlcat(filepath, FILEPREFIX, FILEPATH_LEN);
		number = ft_itoa(*serial_number);
		ft_strlcat(filepath, number, FILEPATH_LEN);
		free(number);
		ft_strlcat(filepath, ".bmp", FILEPATH_LEN);
		fd = open(filepath, O_WRONLY | O_CREAT | O_EXCL, 0664);
		if (fd == -1 && errno == EEXIST)
		{
			*serial_number += 1;
			continue ;
		}
		else if (fd == -1)
			rt_perror(scene, RT_SCENE);
		break ;
	}
	return (fd);
}

void	rt_save_to_bmp_files(t_scene *scene)
{
	t_list		*elem;
	t_image		*img;
	char		*header;
	int			serial_number;
	int			fd;

	serial_number = 1;
	elem = scene->cameras;
	header = rt_init_header(scene);
	while (elem != NULL)
	{
		img = ((t_camera *)elem->content)->viewport;
		fd = rt_open_bmp_file(&serial_number, scene);
		ft_write(fd, header, BMP_HEADER_SIZE + DIB_HEADER_SIZE);
		ft_write(fd, img->byte_array, img->bytes_per_line * scene->height);
		elem = elem->next;
		++serial_number;
	}
	free(header);
	rt_free_scene(scene);
}
