# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 16:08:02 by lfallet           #+#    #+#              #
#    Updated: 2020/06/25 22:28:13 by lfallet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = Cub3D
NAME_BONUS = Cub3D_bonus
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
ifneq ($(opti), 0)
	CFLAGS += -O3
endif

CC = gcc

INCLUDES = ./includes/
INCLUDES_LIB = ./libft/includes/

HEADER = $(INCLUDES)cub3d.h
HEADER_BONUS = $(INCLUDES)cub3d_bonus.h

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
SRCS += init_textsprite.c
SRCS += key_hubmoove.c
SRCS += moove.c
SRCS += look_utilsmoove.c
SRCS += sprite.c
SRCS += sprite_draw.c
SRCS += exit.c
SRCS += savemode.c

SRCS_BONUS += ft_cub3d_bonus.c
SRCS_BONUS += errors_bonus.c
SRCS_BONUS += initialisation_bonus.c
SRCS_BONUS += parser_bonus.c
SRCS_BONUS += parser_map_bonus.c
SRCS_BONUS += utils_parser_map_bonus.c
SRCS_BONUS += recuperation_map_bonus.c
SRCS_BONUS += utils_parser_color_bonus.c
SRCS_BONUS += utils_parser_resolution_bonus.c
SRCS_BONUS += utils_parser_texture_bonus.c
SRCS_BONUS += start_graph_bonus.c
SRCS_BONUS += raycasting_bonus.c
SRCS_BONUS += draw_bonus.c
SRCS_BONUS += utils_bonus.c
SRCS_BONUS += init_bonus.c
SRCS_BONUS += init_textsprite_bonus.c
SRCS_BONUS += key_hubmoove_bonus.c
SRCS_BONUS += moove_bonus.c
SRCS_BONUS += look_utilsmoove_bonus.c
SRCS_BONUS += sprite_bonus.c
SRCS_BONUS += sprite_draw_bonus.c
SRCS_BONUS += exit_bonus.c
SRCS_BONUS += savemode_bonus.c
SRCS_BONUS += life_bonus.c
SRCS_BONUS += minimap_bonus.c
SRCS_BONUS += minimap_utils_bonus.c
SRCS_BONUS += life_utils_bonus.c

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
OBJS_BONUS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS_BONUS))

all : $(MLX) $(LIB)
	$(MAKE) $(NAME)

bonus : $(MLX) $(LIB)
	$(MAKE) bonus_comp

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<  -I $(INCLUDES) -I $(INCLUDES_LIB) -I ./minilibx -o $@

$(OBJS_BONUS): $(OBJ_DIR)%.o: %.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $<  -I $(INCLUDES) -I $(INCLUDES_LIB) -I ./minilibx -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -I$(INCLUDES_LIB) -I./minilibx -L./libft -lft -L./minilibx -lmlx_Linux -lX11 -lm -lbsd -lXext -o $@
	echo "\033[32m$@ is ready !\033[0m"

bonus_comp: $(OBJ_DIR) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -I$(INCLUDES) -I$(INCLUDES_LIB) -I./minilibx -L./libft -lft -L./minilibx -lmlx_Linux -lX11 -lm -lbsd -lXext -o $(NAME)
	echo "\033[32m$(NAME) is ready !\033[0m"

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

.PHONY: all clean fclean re bonus bonus_comp FORCE
#.SILENT:
