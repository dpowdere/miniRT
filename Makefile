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

OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

LIBX	:=	libmlx
LIBFT	:=	libft

DEPX	:=	$(shell find $(LIBX) -name '*.[ch]')
DEPFT	:=	$(shell find $(LIBFT) -name '*.[ch]')

SRCDIR := src
INCDIR := include
OBJDIR := .o

VPATH := $(OBJDIR):$(SRCDIR):$(INCDIR)

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
DFLAGS	:=	-MMD -MP
LIBS	:=	-lmlx -framework OpenGL -framework AppKit -lz
LDIR	:=	-L$(LIBX) -L$(LIBFT)
HDIR	:=	-I$(INCDIR) -I$(LIBX) -I$(LIBFT)

# if on Linux
ifneq ($(findstring linux,$(shell $(CC) -dumpmachine)),)
  LIBS	:=	-lft -lmlx -lXext -lX11
endif

$(shell mkdir -p $(OBJDIR))

.PHONY: all clean fclean norm re run

$(NAME): $(OBJS) .ft .mlx
	$(CC) $(CFLAGS) $(HDIR) $(LDIR) $(addprefix $(OBJDIR)/,$(OBJS)) $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(HDIR) $(LDIR) -c $< $(LIBS) -o $(OBJDIR)/$@

.mlx: $(DEPX)
	$(MAKE) -C $(LIBX)
	@touch $@

.ft: $(DEPFT)
	$(MAKE) -C $(LIBFT)
	@touch $@

all: $(NAME)

clean:
	$(MAKE) -C $(LIBX) clean
	$(MAKE) -C $(LIBFT) fclean
	$(RM) .ft .mlx
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./miniRT

norm:
	~/norm.sh *.[ch]

-include $(DEPS)
