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
	rt_bmp.c \
	rt_error.c \
	rt_free.c \
	rt_image.c \
	rt_intersection.c \
	rt_parse.c \
	rt_parse_config_line.c \
	rt_quadratic.c \
	rt_render.c \
	rt_scene.c \
	rt_vectors.c \
\
	rt_ambient.c \
	rt_camera.c \
	rt_cylinder.c \
	rt_light.c \
	rt_plane.c \
	rt_resolution.c \
	rt_sphere.c \
	rt_square.c \
	rt_triangle.c

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

VPATH := $(OBJDIR):$(SRCDIR):$(INCDIR)

CC			:=	gcc
CPPFLAGS	=	-MMD -MP -MT $@ -I$(INCDIR) -I$(LIBX) -I$(LIBFT)
CFLAGS		:=	-Wall -Wextra -Werror -c
LDFLAGS		:=	-L$(LIBX) -L$(LIBFT)
LDLIBS		:=	-lm -lft -lmlx -framework OpenGL -framework AppKit -lz
ifdef ON_LINUX
  LDLIBS := -lm -lft -lmlx -lXext -lX11
endif
ifdef DEBUG
  CPPFLAGS += -DDEBUG=1
  CFLAGS += -g3
  LDFLAGS += -g3
endif

OPEN := open
ifdef ON_LINUX
  OPEN := xdg-open
endif

$(shell mkdir -p $(OBJDIR))

.PHONY: all clean debug deps-install-linux fclean norm re run save

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
	$(RM) $(NAME) *.dSYM core* *.bmp

re: fclean all

run: all
	./$(NAME) assets/sphere.rt

save: all
	./$(NAME) assets/sphere.rt --save
	ls *.bmp | xargs -L1 $(OPEN)

debug:
	test $(NAME) -nt core && gdb ./$(NAME) || gdb ./$(NAME) core

norm:
	~/norm.sh $(SRCDIR) $(INCDIR)
#	norminette -R CheckForbiddenSourceHeader $(SRCDIR) $(INCDIR)
#	norminette -R CheckDefine $(SRCDIR) $(INCDIR)
#	norminette $(SRCDIR) $(INCDIR)

deps-install-linux:
	sudo apt-get install gcc make xorg libxext-dev libbsd-dev

-include $(DEPLST)
