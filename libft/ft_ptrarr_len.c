/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrarr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 00:55:53 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 01:05:52 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** Useful to count the number of elements of a pointer array
** such as the result of `ft_split` or `ft_split_const`.
*/

size_t	ft_ptrarr_len(void *const *arr)
{
	size_t	len;

	len = 0;
	while (arr != NULL && arr[len])
		++len;
	return (len);
}
