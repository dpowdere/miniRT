/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_big_endian.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 01:14:56 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/24 01:20:31 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_big_endian(void)
{
	const int	x = 1;

	return (!*(unsigned char *)&x);
}
