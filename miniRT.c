/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 22:36:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/01 22:39:03 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <mlx.h>

int	main(void)
{
	void *x;
	void *window;

	x = mlx_init();
	if (x == NULL)
		return (1);
	window = mlx_new_window(x, 900, 600, "miniRT");
	if (window == NULL)
		return (2);
	mlx_clear_window(x, window);
	while (1)
		;
	mlx_destroy_window(x, window);
	return (0);
}
