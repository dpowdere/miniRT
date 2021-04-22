/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:47:29 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/21 23:40:15 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

#define STDOUT	1
#define STDERR	2

void	ft_putendl_fd(const char *s, int fd)
{
	if (fd < 0)
		return ;
	if (s)
		write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

void	ft_println(const char *s)
{
	ft_putendl_fd(s, STDOUT);
}

void	ft_eprintln(const char *s)
{
	ft_putendl_fd(s, STDERR);
}
