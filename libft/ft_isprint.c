/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:47:14 by dpowdere          #+#    #+#             */
/*   Updated: 2020/11/03 00:09:12 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 'isprint' test for any printing character. It should be distinguished
** from 'isgraph' function that tests for any printing character except
** space (' ').
**
** According to the book "Plauger, P.J. The Standard C Library. 1991"
** (P. 28, 30) printing characters complement control characters within the
** ASCII character set:
**
**   The term printing character refers to a member of an
**   implementation-defined set of characters, each of which occupies one
**   printing position on a display device; the term control character refers
**   to a member of an implementation-defined set of characters that are not
**   printing characters.
**
**   [...] In an implementation that uses the seven-bit ASCII character set,
**   the printing characters are those whose values lie from 0x20 (space)
**   through 0x7E (tilde); the control characters are those whose vaiues lie
**   from 0 (NUL) through OxlF (US), and the character 0x7F (DEL).
*/

int	ft_isprint(int c)
{
	return (' ' <= c && c < 127);
}
