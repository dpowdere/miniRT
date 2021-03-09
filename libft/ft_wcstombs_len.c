/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:26:24 by dpowdere          #+#    #+#             */
/*   Updated: 2021/01/25 17:56:25 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <wchar.h>

#include "libft.h"

/*
** Calculate the length of the UTF-32 encoded wide char
** string, when converted to UTF-8.
**
**  - The encoding of the `s` wide char string is always
**    considered to be UTF-32, thus a wrong result will
**    be produced on Windows with its UTF-16, as well
**    as on other non UTF-32 wide char platforms;
**
**  - The encoding of output string is always supposed
**    to be UTF-8;
**
**  - From 1 to 6 UTF-8 bytes per unicode point according
**    to obsolete [RFC 2279](https://tools.ietf.org/html/rfc2279#page-4)
**    (sic!), not [RFC 3629](https://tools.ietf.org/html/rfc3629#page-4)
**    that requires no more than 4 bytes per unicode point.
**
**  Cf. stdlib's `wcstombs` function.
*/

size_t	ft_wcstombs_len(const wchar_t *s)
{
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	while (s[i] != L'\0')
		len += ft_wctomb_len(s[i++]);
	return (len);
}
