# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 16:08:02 by lfallet           #+#    #+#              #
#    Updated: 2020/05/20 17:45:33 by lfallet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = cub3d
LIBDIR = ./libft
LIB = $(LIBDIR)libft.a

CFLAGS += -Wall
CFLAGS += -Wextra
ifeq ($(debug), 0)
	CFLAGS += -g3
else ifeq ($(debug), 1)
	CFLAGS += -fsanitize=address
	CFLAGS += -g3
else ifeq ($(debug), 2)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
else ifeq ($(debug), 3)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -Wpadded
else ifeq ($(debug), 4)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -Wpadded
	ifneq ($(CC), gcc)
		CFLAGS += -Weverything
	endif
endif
ifeq ($(err), 0)
	CFLAGS += -g3
else
	CFLAGS += -Werror
endif

CC = gcc

INCLUDES = ./includes/
INCLUDES_LIB = ./libft/includes/

HEADER = $(INCLUDES)cub3d.h

SRCS += ft_cub3d.c
SRCS += errors.c
SRCS += initialisation.c
SRCS += parser.c
SRCS += parser_map.c
SRCS += utils_parser_map.c
SRCS += recuperation_map.c
SRCS += utils_parser_color.c
SRCS += utils_parser_resolution.c
SRCS += utils_parser_texture.c
SRCS += start_graph.c
SRCS += raycasting.c
SRCS += draw.c
SRCS += utils.c
SRCS += init.c
SRCS += textures.c
SRCS += key.c

OBJ_DIR = ./objs/

vpath %.c sources/
vpath %.c sources/parser/
vpath %.c sources/parser/utils_parser
vpath %.c sources/parser/map
vpath %.c sources/parser/color
vpath %.c sources/parser/resolution
vpath %.c sources/parser/texture
vpath %.c sources/graphical

MLX = minilibx/libmlx_Linux.a

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all : $(MLX) $(LIB)
	$(MAKE) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<  -I $(INCLUDES) -I $(INCLUDES_LIB) -I ./minilibx -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -I$(INCLUDES_LIB) -I./minilibx -L./libft -lft -L./minilibx -lmlx_Linux -lX11 -lm -lbsd -lXext -o $@

$(OBJ_DIR):
	mkdir $@

$(LIB) : FORCE
	$(MAKE) -C $(LIBDIR)

$(MLX) : FORCE
	$(MAKE) -C minilibx 2>/dev/null

FORCE :

clean :
	$(MAKE) clean -C $(LIBDIR)
	$(MAKE) clean -C minilibx 2>/dev/null
	$(RM) -R $(OBJ_DIR)

fclean : clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME)

re : fclean
	$(MAKE)

.PHONY: all clean fclean re FORCE
#.SILENT:
