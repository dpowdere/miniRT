/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 23:01:39 by dpowdere          #+#    #+#             */
/*   Updated: 2021/03/03 23:08:16 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_EVENTS_H
# define RT_EVENTS_H

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

# define XEVENT_KEY_PRESS				2
# define XEVENT_KEY_RELEASE				3
# define XEVENT_BUTTON_PRESS			4
# define XEVENT_BUTTON_RELEASE			5
# define XEVENT_MOTION_NOTIFY			6
# define XEVENT_ENTER_NOTIFY			7
# define XEVENT_LEAVE_NOTIFY			8
# define XEVENT_FOCUS_IN				9
# define XEVENT_FOCUS_OUT				10
# define XEVENT_KEYMAP_NOTIFY			11
# define XEVENT_EXPOSE					12
# define XEVENT_GRAPHICS_EXPOSE			13
# define XEVENT_NO_EXPOSE				14
# define XEVENT_VISIBILITY_NOTIFY		15
# define XEVENT_CREATE_NOTIFY			16
# define XEVENT_DESTROY_NOTIFY			17
# define XEVENT_RESIZE_REQUEST			25
# define XEVENT_CLIENT_MESSAGE			33

# define XMASK_NO_EVENT					0L
# define XMASK_KEY_PRESS				(1L << 0)
# define XMASK_KEY_RELEASE				(1L << 1)
# define XMASK_BUTTON_PRESS				(1L << 2)
# define XMASK_BUTTON_RELEASE			(1L << 3)
# define XMASK_ENTER_WINDOW				(1L << 4)
# define XMASK_LEAVE_WINDOW				(1L << 5)
# define XMASK_POINTER_MOTION			(1L << 6)
# define XMASK_POINTER_MOTION_HINT		(1L << 7)
# define XMASK_BUTTON1_MOTION			(1L << 8)
# define XMASK_BUTTON2_MOTION			(1L << 9)
# define XMASK_BUTTON3_MOTION			(1L << 10)
# define XMASK_BUTTON4_MOTION			(1L << 11)
# define XMASK_BUTTON5_MOTION			(1L << 12)
# define XMASK_BUTTON_MOTION			(1L << 13)
# define XMASK_KEYMAP_STATE				(1L << 14)
# define XMASK_EXPOSURE					(1L << 15)
# define XMASK_VISIBILITY_CHANGE		(1L << 16)
# define XMASK_STRUCTURE_NOTIFY			(1L << 17)
# define XMASK_RESIZE_REDIRECT			(1L << 18)
# define XMASK_SUBSTRUCTURE_NOTIFY		(1L << 19)
# define XMASK_SUBSTRUCTURE_REDIRECT	(1L << 20)
# define XMASK_FOCUS_CHANGE				(1L << 21)

#endif
