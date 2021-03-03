# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 22:31:34 by dpowdere          #+#    #+#              #
#    Updated: 2021/03/03 23:26:22 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRCS := \
	minirt.c \
	color.c

LIBX	:=	./minilibx
LIBFT	:=	./libft

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
DFLAGS	:=	-MMD -MP
LIB		:=	-lmlx -framework OpenGL -framework AppKit -lz
LDIR	:=	-L$(LIBX) -L$(LIBFT)
HDIR	:=	-I$(LIBX) -I$(LIBFT)

OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

# if on Linux
ifneq ($(findstring linux,$(shell $(CC) -dumpmachine)),)
  LIB	:=	-lmlx -lXext -lX11
endif

.PHONY: all clean fclean norm re run

$(NAME): $(OBJS) $(LIBX)/minilibx.a
	$(CC) $(CFLAGS) $(HDIR) $(LDIR) $^ $(LIB) -o $@

%.o: %.c $(LIBX)/minilibx.a
	$(CC) $(CFLAGS) $(DFLAGS) $(HDIR) $(LDIR) -c $< $(LIB)

$(LIBX)/minilibx.a:
	$(MAKE) -C $(LIBX)

all: $(NAME)

clean:
	$(MAKE) -C $(LIBX) clean
	$(RM) *.o *.d

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./miniRT

norm:
	~/norm.sh *.[ch]

-include $(DEPS)
