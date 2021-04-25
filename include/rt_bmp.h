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
# define SH_BMP_RESERVED	6
# define SH_BMP_DATAOFFSET	10

/*
** DIB header in BITMAPCOREHEADER format
*/
# define LEN_DIB_CR_SIZE	4
# define LEN_DIB_CR_WIDTH	2
# define LEN_DIB_CR_HEIGHT	2
# define LEN_DIB_CR_PLANES	2
# define LEN_DIB_CR_BPP		2

# define SH_DIB_CR_SIZE		14
# define SH_DIB_CR_WIDTH	18
# define SH_DIB_CR_HEIGHT	20
# define SH_DIB_CR_PLANES	22
# define SH_DIB_CR_BPP		24

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

# define SH_DIB_NF_SIZE			14
# define SH_DIB_NF_WIDTH		18
# define SH_DIB_NF_HEIGHT		22
# define SH_DIB_NF_PLANES		26
# define SH_DIB_NF_BPP			28
# define SH_DIB_NF_COMPRESSION	30
# define SH_DIB_NF_IMAGE_SIZE	34
# define SH_DIB_NF_XPPM			38
# define SH_DIB_NF_YPPM			42
# define SH_DIB_NF_USED_COLORS	46
# define SH_DIB_NF_IMPT_COLORS	50

#endif
