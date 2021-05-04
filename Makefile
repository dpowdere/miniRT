# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 22:31:34 by dpowdere          #+#    #+#              #
#    Updated: 2021/04/28 16:07:09 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRCS := \
	minirt.c \
\
	rt_bmp.c \
	rt_color.c \
	rt_config_line.c \
	rt_error.c \
	rt_illumination.c \
	rt_image.c \
	rt_intersection.c \
	rt_orientation.c \
	rt_parse.c \
	rt_quadratic.c \
	rt_render.c \
	rt_scene.c \
	rt_screen.c \
	rt_vectors1.c \
	rt_vectors2.c \
	rt_vectors3.c \
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
LIBX	:=	libmlx/macos_metal
ifdef ON_LINUX
  LIBX	:=	libmlx/linux
endif

DEPX	:=	$(shell find $(LIBX) -name '*.[ch]')
DEPFT	:=	$(shell find $(LIBFT) -name '*.[ch]')
STUBX	:=	.Makestub.mlx
STUBFT	:=	.Makestub.ft

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
LDLIBS		:=	-lm -lft -lmlx
ifdef ON_LINUX
  LDLIBS	+=	-lXext -lX11
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

INSTALL_NAME_TOOL_AVAILABLE := 0
ifndef ON_LINUX
  INSTALL_NAME_TOOL_AVAILABLE := $(shell which install_name_tool \
    1>/dev/null 2>&1 \
    && echo 1 || echo 0)
endif

$(shell mkdir -p $(OBJDIR))

.PHONY: all clean debug deps-install-linux fclean norm re run save

$(NAME): $(OBJS) $(STUBFT) $(STUBX)
	$(CC) $(LDFLAGS) -o $@ $(OBJLST) $(LDLIBS)
ifndef ON_LINUX
  ifeq ($(INSTALL_NAME_TOOL_AVAILABLE), 0)
	@cp $(LIBX)/libmlx.dylib .
  else
	@install_name_tool -change libmlx.dylib $(LIBX)/libmlx.dylib $(NAME)
  endif
endif

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(OBJDIR)/$@ $<

$(STUBX): $(DEPX)
	@$(MAKE) -C $(LIBX)
	@touch $@

$(STUBFT): $(DEPFT)
	@$(MAKE) -C $(LIBFT)
	@touch $@

all: $(NAME)

clean:
	@$(MAKE) -C $(LIBX) clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(RM) $(STUBFT) $(STUBX)
	$(RM) -r $(OBJDIR)/*.o $(OBJDIR)/*.d

fclean: clean
	$(RM) -r $(NAME) *.dSYM core* *.bmp

re: fclean all

run: all
	-./$(NAME) assets/test.rt

save: all
	-./$(NAME) assets/test.rt --save
	ls *.bmp | xargs -L1 $(OPEN)

debug:
	test $(NAME) -nt core && gdb ./$(NAME) || gdb ./$(NAME) core

norm:
	norminette $(SRCDIR) $(INCDIR) $(LIBFT) | grep -v 'OK!' || true

deps-install-linux:
	sudo apt-get install gcc make xorg libxext-dev libbsd-dev

-include $(DEPLST)
