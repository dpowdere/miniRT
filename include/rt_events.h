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
# define XMASK_KEY_PRESS				1L
# define XMASK_KEY_RELEASE				2L
# define XMASK_BUTTON_PRESS				4L
# define XMASK_BUTTON_RELEASE			8L
# define XMASK_ENTER_WINDOW				16L
# define XMASK_LEAVE_WINDOW				32L
# define XMASK_POINTER_MOTION			64L
# define XMASK_POINTER_MOTION_HINT		128L
# define XMASK_BUTTON1_MOTION			256L
# define XMASK_BUTTON2_MOTION			512L
# define XMASK_BUTTON3_MOTION			1024L
# define XMASK_BUTTON4_MOTION			2048L
# define XMASK_BUTTON5_MOTION			4096L
# define XMASK_BUTTON_MOTION			8192L
# define XMASK_KEYMAP_STATE				16384L
# define XMASK_EXPOSURE					32768L
# define XMASK_VISIBILITY_CHANGE		65536L
# define XMASK_STRUCTURE_NOTIFY			131072L
# define XMASK_RESIZE_REDIRECT			262144L
# define XMASK_SUBSTRUCTURE_NOTIFY		524288L
# define XMASK_SUBSTRUCTURE_REDIRECT	1048576L
# define XMASK_FOCUS_CHANGE				2097152L

# ifdef __APPLE__
#  define KEY_ENTER	36
#  define KEY_ESQ	53
#  define KEY_Q		12

#  define XEVENT_X  XEVENT_DESTROY_NOTIFY
#  define XMASK_X   XMASK_VISIBILITY_CHANGE
# endif

# ifdef __linux__
#  define KEY_ENTER	65293
#  define KEY_ESQ	65307
#  define KEY_Q		113

/*
** NOTE: For closing a window on Linux see `ClientMessage` X event
** https://tronche.com/gui/x/xlib/events/ and `WM_DELETE_WINDOW` ICCCM
** protocol https://tronche.com/gui/x/icccm/sec-4.html#s-4.2.8.1
*/
#  define XEVENT_X  XEVENT_CLIENT_MESSAGE
#  define XMASK_X   XMASK_NO_EVENT
# endif

#endif
