# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 22:31:34 by dpowdere          #+#    #+#              #
#    Updated: 2021/03/01 22:36:07 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

LIBX	:=	./minilibx
LIBFT	:=	./libft

CFLAGS	:=	-Wall -Wextra -Werror
LIB		:=	-lmlx -framework OpenGL -framework AppKit -lz
LDIR	:=	-L$(LIBX) -L$(LIBFT)
HDIR	:=	-I$(LIBX) -I$(LIBFT)

# if on Linux
ifneq ($(findstring linux,$(shell $(CC) -dumpmachine)),)
  LIB	:=	-lmlx -lXext -lX11
endif

.PHONY: all clean fclean norm re run

$(NAME): minirt.c color.c
	$(MAKE) -C $(LIBX)
	$(CC) $(CFLAGS) $(HDIR) $(LDIR) $^ $(LIB) -o $@

all: $(NAME)

clean:
	$(MAKE) -C $(LIBX) clean
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./miniRT

norm:
	~/norm.sh *.[ch]
