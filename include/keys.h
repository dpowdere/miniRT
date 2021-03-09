/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 23:01:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/03 23:08:16 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__
#  define KEY_ENTER	36
#  define KEY_ESQ	53
#  define KEY_Q		12
# endif

# ifdef __linux__
#  define KEY_ENTER	65293
#  define KEY_ESQ	65307
#  define KEY_Q		113
# endif

#endif
