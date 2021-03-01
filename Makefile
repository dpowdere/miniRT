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

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
LIB		:=	-lmlx -lXext -lX11
LIBINC	:=	-L $(LIBX)
INC		:=	-I $(LIBX)

.PHONY: all clean fclean re

$(NAME): $(NAME).c
	$(MAKE) -C $(LIBX)
	$(CC) $(CFLAGS) $(INC) $(LIBINC) $< $(LIB) -o $@

all: $(NAME)

clean:
	$(MAKE) -C $(LIBX) clean
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all
