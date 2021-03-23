# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 22:31:34 by dpowdere          #+#    #+#              #
#    Updated: 2021/03/11 18:25:08 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRCS := \
	minirt.c \
\
	rt_color.c \
	rt_error.c \
	rt_free.c \
	rt_image.c \
	rt_parse.c \
	rt_parse_config_line.c \
	rt_scene.c \
\
	rt_parse_ambient.c \
	rt_parse_camera.c \
	rt_parse_cylinder.c \
	rt_parse_light.c \
	rt_parse_plane.c \
	rt_parse_resolution.c \
	rt_parse_sphere.c \
	rt_parse_square.c \
	rt_parse_triangle.c

ifneq ($(findstring linux,$(shell $(CC) -dumpmachine)),)
  define ON_LINUX =

    We are on linux!

    Just a quick reminder on how to define
    a multiline variable value in Makefiles.

    See https://www.gnu.org/software/make/manual/html_node/Multi_002dLine.html

  endef
endif

OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

LIBFT	:=	libft
LIBX	:=	libmlx/macos_opengl
ifdef ON_LINUX
  LIBX	:=	libmlx/linux
endif

DEPX	:=	$(shell find $(LIBX) -name '*.[ch]')
DEPFT	:=	$(shell find $(LIBFT) -name '*.[ch]')

SRCDIR := src
INCDIR := include
OBJDIR := .tmp
OBJLST := $(addprefix $(OBJDIR)/,$(OBJS))
DEPLST := $(addprefix $(OBJDIR)/,$(DEPS))

VPATH := $(OBJDIR):$(SRCDIR):$(INCDIR):.

CC			:=	gcc
CPPFLAGS	=	-MMD -MP -MT $@ -I$(INCDIR) -I$(LIBX) -I$(LIBFT)
CFLAGS		:=	-Wall -Wextra -Werror -c
LDFLAGS		:=	-L$(LIBX) -L$(LIBFT)
LDLIBS		:=	-lm -lft -lmlx -framework OpenGL -framework AppKit -lz
ifdef ON_LINUX
  LDLIBS := -lm -lft -lmlx -lXext -lX11
endif
ifdef DEBUG
  CFLAGS += -g3
endif

$(shell mkdir -p $(OBJDIR))

.PHONY: all clean fclean norm re run

$(NAME): $(OBJS) .ft .mlx
	$(CC) $(LDFLAGS) -o $@ $(OBJLST) $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(OBJDIR)/$@ $<

.mlx: $(DEPX)
	@$(MAKE) -C $(LIBX)
	@touch $@

.ft: $(DEPFT)
	@$(MAKE) -C $(LIBFT)
	@touch $@

all: $(NAME)

clean:
	@$(MAKE) -C $(LIBX) clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(RM) .ft .mlx
	$(RM) -r $(OBJDIR)/*.o $(OBJDIR)/*.d

fclean: clean
	$(RM) $(NAME) *.dSYM

re: fclean all

run: all
	./miniRT assets/subject.rt

norm:
	~/norm.sh $(SRCDIR) $(INCDIR)
#	norminette -R CheckForbiddenSourceHeader $(SRCDIR) $(INCDIR)
#	norminette -R CheckDefine $(SRCDIR) $(INCDIR)
#	norminette $(SRCDIR) $(INCDIR)

-include $(DEPLST)
