/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 05:59:07 by dpowdere          #+#    #+#             */
/*   Updated: 2021/04/15 16:22:06 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_BMP_H
# define RT_BMP_H

/*
** BMP with a DIB header in BITMAPCOREHEADER format.
** It is enough for our needs, and pretty simple. However, it is
** considered outdated and some viewers do not support it.
** We could use BITMAPINFOHEADER, BITMAPV4HEADER or BITMAPV5HEADER
** formats instead.
*/

# define RT_DIB_HEADER			rt_dib_bitmapinfoheader
# define DIB_HEADER_SIZE		BITMAPINFOHEADER_SIZE

# define DIB_BYTE_FACTOR		4
# define PIXELS_PER_METER		10000

# define BMP_HEADER_SIZE		14

# define BITMAPCOREHEADER_SIZE	12
# define BITMAPINFOHEADER_SIZE	40
# define BITMAPV4HEADER_SIZE	108
# define BITMAPV5HEADER_SIZE	124

/*
** BMP file header
*/
# define LEN_BMP_TYPE		2
# define LEN_BMP_FILESIZE	4
# define LEN_BMP_RESERVED	4
# define LEN_BMP_DATAOFFSET	4

# define SH_BMP_TYPE		0
# define SH_BMP_FILESIZE	LEN_BMP_TYPE
# define SH_BMP_RESERVED	(SH_BMP_FILESIZE + LEN_BMP_FILESIZE)
# define SH_BMP_DATAOFFSET	(SH_BMP_RESERVED + LEN_BMP_RESERVED)

/*
** DIB header in BITMAPCOREHEADER format
*/
# define LEN_DIB_CR_SIZE	4
# define LEN_DIB_CR_WIDTH	2
# define LEN_DIB_CR_HEIGHT	2
# define LEN_DIB_CR_PLANES	2
# define LEN_DIB_CR_BPP		2

# define SH_DIB_CR_SIZE		(SH_BMP_DATAOFFSET + LEN_BMP_DATAOFFSET)
# define SH_DIB_CR_WIDTH	(SH_DIB_CR_SIZE + LEN_DIB_CR_SIZE)
# define SH_DIB_CR_HEIGHT	(SH_DIB_CR_WIDTH + LEN_DIB_CR_WIDTH)
# define SH_DIB_CR_PLANES	(SH_DIB_CR_HEIGHT + LEN_DIB_CR_HEIGHT)
# define SH_DIB_CR_BPP		(SH_DIB_CR_PLANES + LEN_DIB_CR_PLANES)

/*
** DIB header in BITMAPINFOHEADER format
*/
# define LEN_DIB_NF_SIZE			LEN_DIB_CR_SIZE
# define LEN_DIB_NF_WIDTH			4
# define LEN_DIB_NF_HEIGHT			4
# define LEN_DIB_NF_PLANES			LEN_DIB_CR_PLANES
# define LEN_DIB_NF_BPP				LEN_DIB_CR_BPP
# define LEN_DIB_NF_COMPRESSION		4
# define LEN_DIB_NF_IMAGE_SIZE		4
# define LEN_DIB_NF_XPPM			4
# define LEN_DIB_NF_YPPM			4
# define LEN_DIB_NF_USED_COLORS		4
# define LEN_DIB_NF_IMPT_COLORS		4

# define DIB_COMPRESSION_RGB			0
# define DIB_ALL_COLORS_ARE_USED		0
# define DIB_ALL_COLORS_ARE_IMPORTANT	0

# define SH_DIB_NF_SIZE			(SH_BMP_DATAOFFSET + LEN_BMP_DATAOFFSET)
# define SH_DIB_NF_WIDTH		(SH_DIB_NF_SIZE + LEN_DIB_NF_SIZE)
# define SH_DIB_NF_HEIGHT		(SH_DIB_NF_WIDTH + LEN_DIB_NF_WIDTH)
# define SH_DIB_NF_PLANES		(SH_DIB_NF_HEIGHT + LEN_DIB_NF_HEIGHT)
# define SH_DIB_NF_BPP			(SH_DIB_NF_PLANES + LEN_DIB_NF_PLANES)
# define SH_DIB_NF_COMPRESSION	(SH_DIB_NF_BPP + LEN_DIB_NF_BPP)
# define SH_DIB_NF_IMAGE_SIZE	(SH_DIB_NF_COMPRESSION + LEN_DIB_NF_COMPRESSION)
# define SH_DIB_NF_XPPM			(SH_DIB_NF_IMAGE_SIZE + LEN_DIB_NF_IMAGE_SIZE)
# define SH_DIB_NF_YPPM			(SH_DIB_NF_XPPM + LEN_DIB_NF_XPPM)
# define SH_DIB_NF_USED_COLORS	(SH_DIB_NF_YPPM + LEN_DIB_NF_YPPM)
# define SH_DIB_NF_IMPT_COLORS	(SH_DIB_NF_USED_COLORS + LEN_DIB_NF_USED_COLORS)

#endif
