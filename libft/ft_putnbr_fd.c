/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:48:12 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/21 21:48:40 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		sign;
	int		power10;
	int		x;
	char	c;

	if (n < 0)
		write(fd, "-", 1);
	sign = 1;
	if (n < 0)
		sign = -1;
	power10 = 1;
	x = n / 10;
	while (x != 0)
	{
		x /= 10;
		power10 *= 10;
	}
	while (power10 != 0)
	{
		x = n / power10;
		c = (unsigned char)('0' + x * sign);
		n %= power10;
		power10 /= 10;
		write(fd, &c, 1);
	}
}
