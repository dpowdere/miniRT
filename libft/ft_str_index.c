/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 03:21:34 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/12 03:27:03 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_index(const char *s, int c)
{
	const char	*e;

	e = s;
	while (*e && *e != (unsigned char)c)
		++e;
	if (*e == '\0' && (unsigned char)c != '\0')
		return (-1);
	return ((int)(e - s));
}
