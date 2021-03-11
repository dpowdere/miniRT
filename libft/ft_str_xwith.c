/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_xwith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 23:19:48 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/11 23:33:52 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"

int	ft_str_startswith(const char *s, const char *prefix)
{
	size_t	len;

	len = ft_strlen(prefix);
	return (!ft_strncmp(s, prefix, len));
}

int	ft_str_endswith(const char *s, const char *suffix)
{
	size_t	suffix_len;
	size_t	s_len;

	suffix_len = ft_strlen(suffix);
	s_len = ft_strlen(s);
	if (s_len < suffix_len)
		return (0);
	return (!ft_strncmp(s + s_len - suffix_len, suffix, suffix_len));
}
