/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcslen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:40:35 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/24 19:42:46 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <wchar.h>

size_t	ft_wcslen(const wchar_t *s)
{
	size_t	len;

	len = 0;
	while (s[len] != L'\0')
		++len;
	return (len);
}
