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
OBJLST := $(addprefix $(OBJDIR)/,$(OBJS))

VPATH := $(OBJDIR):$(SRCDIR):$(INCDIR)

DFLAGS	:=	-MMD -MP
HPATHS	:=	-I$(INCDIR) -I$(LIBX) -I$(LIBFT)

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror $(DFLAGS) $(HPATHS) -c
LDLIBS	:=	-lmlx -framework OpenGL -framework AppKit -lz
LDFLAGS	:=	-L$(LIBX) -L$(LIBFT)

# if on Linux
ifneq ($(findstring linux,$(shell $(CC) -dumpmachine)),)
  LDLIBS := -lft -lmlx -lXext -lX11
endif

$(shell mkdir -p $(OBJDIR))

.PHONY: all clean fclean norm re run

$(NAME): $(OBJS) .ft .mlx
	$(CC) $(LDFLAGS) -o $@ $(OBJLST) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/$@ $<

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
	$(RM) $(NAME) *.dSYM

re: fclean all

run: all
	./miniRT

norm:
	~/norm.sh $(SRCDIR) $(INCDIR)
	#norminette -R CheckForbiddenSourceHeader $(SRCDIR) $(INCDIR)
	#norminette -R CheckDefine $(SRCDIR) $(INCDIR)
	#norminette $(SRCDIR) $(INCDIR)

-include $(DEPS)
