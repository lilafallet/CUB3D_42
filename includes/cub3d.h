/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 20:41:48 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 18:05:47 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <limits.h>
# include <errno.h>
# include <math.h>

# ifndef TRUE
#  define TRUE		1
# endif

# ifndef FALSE
#  define FALSE		0
# endif

# ifndef SUCCESS
#  define SUCCESS	0
# endif

# ifndef FAILURE
#  define FAILURE	-1
# endif

/*
**###########_PARSER_##############
*/

# define SCREENSHOT			"screenshot.bmp"
# define ERROR				2
# define NB_INFO 			4
# define ACCESS				NULL
# define COMMA 				','
# define STR_COMMA 			","
# define PATH 				"./"
# define PLUS 				'+'
# define SLASH 				'/'
# define SPACE 				' '
# define STR_TEXTURE 		"NOSOWEEA"
# define STRING_SPACE_TAB	" \t"
# define TAB 				'\t'
# define FIRST_ARG			1
# define SECOND_ARG			2
# define THIRD_ARG			3
# define NO_LINE			0
# define NO_VECTOR			NULL

/*
**###########_TEXTURE_#############
*/

# define NO 				0
# define SO 				1
# define WE 				2
# define EA 				3
# define WAY_WALL_SPRITE 	3
# define S 					4
# define NB_TEXTURE 		5
# define FIRST_TEXTURE 		"NSWE"
# define STR_TEXTURE_NO		"NO"
# define STR_TEXTURE_SO 	"SO"
# define STR_TEXTURE_WE 	"WE"
# define STR_TEXTURE_EA 	"EA"
# define SUP_MAX_TEXT 		2

/*
**###########_COLOR_###############
*/

# define R 					0
# define G 		1
# define B 					2
# define NB_INDIC_COLOR 	2
# define NB_COLOR 			3
# define COLOR_MAX 			255
# define MAX_FACTO 			5
# define MAX_NB_COLOR 		3
# define ONE_COLOR			0
# define TWO_COLOR			1

/*
**##########_RESOLUTION_##########
*/

# define NB_RESOLUTION 		2
# define CHAR_RESOLUTION	'R'
# define STR_RESOLUTION 	"R"
# define STRING_CHECK_R		"SFCNSEW"
# define NB_INDIC_RESOL		0
# define SUP_MAX_RESOL		3
# define NOT_ENOUGH			1
# define TO_MUCH			2

/*
**############_MAP_###############
*/

# define AXE_X 				0
# define COLOR_C 			0
# define WIDTH 				0
# define AXE_Y 				1
# define COLOR_F 			1
# define HEIGHT 			1
# define OUTMAP 			6
# define BUFFER_SIZE 		4096
# define CHAR_WALL 			'1'
# define NORTH 				'N'
# define SOUTH 				'S'
# define WEST 				'W'
# define EAST 				'E'
# define STR_MAP 			"012NSWE \t"

# define GREEN				0x33cc33
# define BLACK				0x000000
# define GREY				0x696969
# define BLUE				0x3333ff
# define RED				0xff0000
# define CASE_MAX_SIZE		20
# define UNDEFINED			-1
# define MAX_WIDTH			1920
# define MAX_HEIGHT			1080
# define MAP_OFFSET			150
# define PLAYER_POS			0
# define MID_NB_MAP			5
# define SIZE_FORMAT		4
# define STR_FORMAT			".cub"

# define MIN_PAD			0.11

/*
** #############################################################################
**_____________________________STRUCTURE MAP____________________________________
**##############################################################################
*/

enum			e_map
{
	WAY,
	WALL,
	SPRITE,
	POSITION,
	OUT,
	STOP,
	WRONG_INFO_MAP
};

typedef struct	s_recup
{
	enum e_map		**tab_map;
	char			*str_texture[NB_TEXTURE];
	char			*str_text_spr;
	char			*str_text_no;
	char			*str_text_so;
	char			*str_text_we;
	char			*str_text_ea;
	int				resolution[NB_RESOLUTION];
	int				posx;
	int				posy;
	int				tab_color_f[NB_COLOR];
	int				tab_color_c[NB_COLOR];
	char			dirpos;
	char			pad[7];
}				t_recup;

typedef struct	s_utils
{
	size_t			nb_line;
	size_t			index_map;
	size_t			max_index;
	size_t			max_line;
	size_t			count_num;
	size_t			count_loops;
	size_t			count_comma;
	size_t			count_line;
	size_t			count_position;
	size_t			save_mode;
	size_t			count_resolution;
	size_t			not_map;
	int				fd;

}				t_utils;

typedef struct	s_map
{
	t_recup			recup;
	t_utils			utils;
}				t_map;

/*
** #############################################################################
**_____________________________STRUCTURE MACHINE________________________________
**##############################################################################
*/

/*
**###########_INFO_#################
*/

# define ALL_INFO		0x000311f

# define BT_NO 			0x0000001
# define BT_SO 			0x0000002
# define BT_WE 			0x0000004
# define BT_EA 			0x0000008
# define BT_SPR			0x0000010
# define BT_RESOLUTION	0x0000100
# define BT_COLOR_F		0x0001000
# define BT_COLOR_C		0x0002000
# define BT_F_RED 		0x0004000
# define BT_F_GREEN 	0x0008000
# define BT_F_BLUE 		0x0010000
# define BT_C_RED 		0x0020000
# define BT_C_GREEN 	0x0040000
# define BT_C_BLUE 		0x0080000
# define BT_POSITION_N 	0x0100000
# define BT_POSITION_S 	0x0200000
# define BT_POSITION_W 	0x0400000
# define BT_POSITION_E 	0x0800000

/*
**###########_ERROR_#################
*/

# define NB_ERROR			28

# define IS_ERROR										0xFFFFFFF000000
# define ERROR_RESOLUTION_NUMBER_ARGUMENTS				0x0000001000000
# define ERROR_TEXTURE_NUMBER_ARGUMENTS					0x0000002000000
# define ERROR_COLOR_WRONG_TYPE_NUMBER					0x0000004000000
# define ERROR_COLOR_NUMBER_COLOR_ARGUMENTS				0x0000008000000
# define ERROR_COLOR_NUMBER_ARGUMENTS					0x0000010000000
# define ERROR_COLOR_ALREADY							0x0000020000000
# define ERROR_MAP_NOT_VALID							0x0000040000000
# define ERROR_RESOLUTION_WRONG_TYPE_NUMBER				0x0000080000000
# define ERROR_RESOLUTION_WRONG_TYPE_INDICATOR			0x0000100000000
# define ERROR_TEXTURE_ALREADY							0x0000200000000
# define ERROR_COLOR_NOT_NUMBER							0x0000400000000
# define ERROR_TEXTURE_FORMAT							0x0000800000000
# define ERROR_MAP_LOT_POSITION							0x0001000000000
# define ERROR_GLOBAL									0x0002000000000
# define ERROR_SAVE										0x0004000000000
# define ERROR_FORMAT									0x0008000000000
# define ERROR_ARG_BIG									0x0010000000000
# define ERROR_ARG_LITTLE								0x0020000000000
# define ERROR_MALLOC_CPYTAB							0x0040000000000
# define ERROR_IMGPTR									0x0080000000000
# define ERROR_WINDATA									0x0100000000000
# define ERROR_MALLOC_RAYBUFF							0x0200000000000
# define ERROR_MALLOC_POS								0x0400000000000
# define ERROR_IMG										0x0800000000000
# define ERROR_DATA										0x1000000000000
# define ERROR_MALLOC_DIST								0x2000000000000
# define ERROR_MLX_PTR									0x4000000000000
# define ERROR_WIN_PTR									0x8000000000000

# define ERR1			"RESOLUTION : the number of information is not good\n"
# define ERR2			"TEXTURE = too much information\n"
# define ERR3			"COLOR = wrong type of number\n"
# define ERR4			"COLOR = number of color is invalid\n"
# define ERR5			"COLOR = data format not good\n"
# define ERR6			"COLOR = already have color\n"
# define ERR7			"MAP = invalid map\n"
# define ERR8			"RESOLUTION = wrong type of number\n"
# define ERR9			"RESOLUTION = wrong type of indicator\n"
# define ERR10			"TEXTURE = already have a texture\n"
# define ERR11			"COLOR = the argument is not a number\n"
# define ERR12			"TEXTURE = no path to the texture\n"
# define ERR13			"MAP = too much information\n"
# define ERR14			"one line is invalid\n"
# define ERR15			"SAVE : if you want to be in save mode : --save\n"
# define ERR16			"ARGUMENTS : wrong format (expecting .cub)\n"
# define ERR17			"ARGUMENTS : to much arguments\n"
# define ERR18			"ARGUMENTS : missing second argument\n"
# define ERR19			"CPY_TAB : malloc failed\n"
# define ERR20			"IMG_PTR : mlx_new_image failed\n"
# define ERR21			"WIN_DATA : mlx_get_data_addr failed\n"
# define ERR22			"RAYBUFF : malloc raybuff failed\n"
# define ERR23			"POS : malloc sprite pos failed\n"
# define ERR24			"IMG : mlx_xmp_file_to_image failed\n"
# define ERR25			"DATA : mlx_get_data_addr failed\n"
# define ERR26			"DIST : malloc dist sprite failed\n"
# define ERR27			"MLX_PTR : mlx_init failed\n"
# define ERR28			"WIN_PTR : mlx_new_window failed\n"
# define FAIL_OPEN_MAP		"Error\nFail to open the map"
# define FAIL_CLOSE_MAP		"Error\nFail to close the map"
# define FAIL_WRITE_HEADER	"Error\nFail to write the header on the bmp file"
# define FAIL_WRITE_COLOR	"Error\nFail to write color on the bmp file"
# define FAIL_WRITE_PADING	"Error\nFail to write the pading on the bmp file"
# define FAIL_CLOSE_SCREEN	"Error\nFail to close the screenshot"

/*
**###########_STATE_#################
*/

enum			e_state
{
	RESOLUTION,
	TEXTURE,
	COLOR,
	MAP
};

/*
**###########_STATE_MACHINE_#################
*/

typedef struct	s_state_machine
{
	unsigned long		info;
	enum e_state		state;
	char				pad[4];
}				t_state_machine;

/*
** #############################################################################
**_____________________________STRUCTURE GRAPH__________________________________
**##############################################################################
*/

/*
**###########_WINDOWS_#################
*/

# define MAX_AXE_X 		1088
# define MAX_AXE_Y 		612
# define WINDOW_NAME	"Cub3D"

typedef struct	s_windows
{
	void			*mlx_ptr;
	void			*img_ptr;
	void			*win_ptr;
	int				*data;
	int				*img_data;
	unsigned long	img_color;
	int				size_line;
	int				bits;
	int				endian;
	int				screenwidth;
	int				screenheight;
	int				mapwidth;
	int				mapheight;
	int				max_screen_width;
	int				max_screen_height;
	char			pad[4];
}				t_windows;

/*
**###########_COLOR_#################
*/

typedef struct	s_color
{
	int		north;
	int		south;
	int		west;
	int		east;
	int		wall;
	int		color_f;
}				t_color;

/*
**###########_RAYCASTING_#################
*/

typedef struct	s_rting
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planecamx;
	double	planecamy;
	double	time;
	double	oldtime;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	distx;
	double	disty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		mv_update;
	char	pad[4];

}				t_raycasting;

/*
**###########_DRAW_#################
*/

typedef struct	s_draw
{
	int		height_line;
	int		start;
	int		end;
	int		no_sky;
	int		bmp_x;
	int		bmp_y;
}				t_draw;

/*
**###########_TEXTURE_#################
*/

typedef struct	s_text
{
	void	*img[NB_TEXTURE];
	double	wallhit;
	double	step;
	double	pos;
	int		*data[NB_TEXTURE];
	int		size[NB_TEXTURE][2];
	int		size_line[NB_TEXTURE];
	int		bits[NB_TEXTURE];
	int		endian[NB_TEXTURE];
	int		texx;
	int		texy;
	int		color;
	int		error_sprite;
}				t_texture;

/*
**###########_MOOVE_#################
*/

# define KEYPRESS			2
# define KEYRELEASE			3
# define EXIT				33
# define KMV_UP				119
# define KMV_DOWN			115
# define KMV_LEFT			97
# define KMV_RIGHT			100
# define K_RESTART			114
# define KLK_LEFT			65361
# define KLK_RIGHT			65363
# define KEY_ESCAPE			65307

# define MV_UP 			0x0000001
# define MV_DOWN 		0x0000002
# define MV_LEFT 		0x0000004
# define MV_RIGHT		0x0000008
# define LK_LEFT		0x0000010
# define LK_RIGHT		0x0000100
# define PRESS			0x0000200
# define RELEASE		0x0000400
# define MOOVE			0x0000800
# define LOOK			0x0001000
# define NOT_WALL		0x0002000
# define CAM			0x0004000
# define RESTART		0x0008000

# define DIR_POS	1
# define DIR_NEG	-1
# define DEGREE		180

typedef struct	s_mv
{
	double	new_posx;
	double	new_posy;
	double	old_posx;
	double	old_posy;
	double	degree_lk;
	double	radius_lk;
	double	new_planecamx;
	double	new_planecamy;
	double	new_dirx;
	double	new_diry;
	double	comb_posx;
	double	comb_posy;
	double	speed_mv;
	double	speed_lk;
	int		log;
	int		mv_dir;
	int		lk_dir;
	int		update;
	int		is_wall;
	int		ydown;
	int		yup;
	int		xright;
	int		stopydown;
	int		stopyup;
	int		stopxright;
	int		tmp_left;
	int		tmp_mv;
	int		tmpl;
	int		tmpd;
	int		tmp_down;
	int		tmpup;
	int		tmp_yp;
	int		tmp_ym;
	int		tmp_xp;
	int		tmp_xm;
	char	pad[4];
}				t_moove;

/*
**###########_SPRITE_#################
*/

# define POW_2				2
# define PIXEL				256
# define PIXEL_DIV2			128

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_position;

typedef struct	s_sp
{
	t_position	*pos;
	double		*raybuff;
	double		*dist;
	double		x;
	double		y;
	double		rot;
	double		playposx;
	double		playposy;
	double		screen_where;
	size_t		nb_sprite;
	int			color;
	int			height;
	int			starty;
	int			endy;
	int			width;
	int			startx;
	int			endx;
	int			textx;
	int			texty;
	int			textw;
	char		pad[4];
	size_t		count;
}				t_sprite;

/*
**###########_BMP_#################
*/

# define HEADERSIZE		54
# define INFODATASIZE	40
# define PIXOFFSET		4
# define BPP			24
# define PLANECOLOR		1
# define XPIXELS		0x0B13
# define YPIXELS		0x0B13
# define FILLOF0		0
# define TYPEFILE0		0
# define FILESIZE2		2
# define PIXOFFSET10	10
# define HEADERSIZE14	14
# define IMGWIDTH18		18
# define IMGHEIGHT22	22
# define PLANECOLOR27	27
# define BPP28			28
# define BUFFSIZE34		34
# define XCOLOR38		38
# define YCOLOR42		42
# define CHAR0			'0'
# define OCTET3			3
# define STR_SAVE		"--save"
# define SIZE_PAD		3

/*
**###########_GRAPH_#################
*/

typedef struct	s_graph
{
	t_windows		win;
	t_color			color;
	t_raycasting	rting;
	t_draw			draw;
	t_texture		text;
	t_moove			mv;
	t_sprite		sp;
}				t_graph;

/*
** #############################################################################
**________________________________FUNCTIONS_____________________________________
**##############################################################################
*/

/*
**###########_PARSER_#################
*/

typedef	int	(*t_function)(t_vector *, t_map *, t_state_machine *);

int				hub_verification_map(t_state_machine *machine, t_vector *line,
										unsigned long nb_line);
void			ft_free(t_map *map, t_vector *line);
int				first_parser(t_map *map, int fd, t_state_machine *machine);
void			printf_errors(unsigned long flag, unsigned long nb_line,
								t_vector *line);
int				is_map(t_vector *vct);
int				recuperation_map(t_vector *line, t_map *map);
int				recuperation_eachelem(t_state_machine *machine,
										size_t count_line, size_t index,
										int flag);
int				verif_line(t_vector *line, t_state_machine *machine,
							size_t count_line);
int				verification_global_map(t_map *map, t_state_machine *machine);
int				realloc_tab(t_map *map, size_t old_index,
								size_t count_line, size_t new_index);
int				iter_map(t_map *map, int (*f)(t_map *map, size_t y, size_t x,
							t_state_machine *machine),
							t_state_machine *machine);
int				clean_and_print(t_map *map, size_t i, size_t j,
									t_state_machine *machine);
int				verif_map(t_map *map, size_t y, size_t x,
							t_state_machine *machine);
int				have_all_info(t_state_machine *machine);
void			is_color(uint8_t *count, t_vector *split,
							t_state_machine *machine,
							const char *tab_color[NB_INDIC_COLOR]);
int				init_machine_color(uint8_t count, t_state_machine *machine,
									t_vector *cp);
void			is_texture(uint8_t *count, t_vector *split,
							t_state_machine *machine,
							const char *tab_texture[NB_TEXTURE]);
void			recuperation_texture(t_state_machine *machine, uint8_t count,
										t_vector *split, t_map *map);
void			is_indic_resolution(t_vector *split, t_state_machine *machine);
void			is_number_resolution(t_vector *split, t_state_machine *machine,
										size_t i, t_map *map);
int				parser_savemode(char *argument, t_map *map);
int				is_good_file(char *str);
int				true_or_false(t_vector *split, t_vector *vct, uint8_t count,
								t_state_machine *machine);
size_t			fill_line(t_map *map, enum e_map **cpy_tab);
t_state_machine	*get_state_machine(t_state_machine *machine);
t_map			*get_map(t_map *map);
t_graph			*graph_holder(t_graph *gr);

/*
**###########_GRAPH_#################
*/

void			start_graph(t_map *map);
void			init_graph(t_graph *gr, t_map *map);
void			process_window(t_graph *gr);
void			init_map(t_map *map, t_graph *gr);
void			get_direction_position(t_map *map, t_graph *gr);
void			get_plane(t_graph *gr, t_map *map);
void			start_raycasting(t_map *map, t_graph *gr);
void			shadow_wall(t_graph *gr);
void			hub_draw(t_map *map, t_graph *gr, int x);
int				get_rgb(int r, int g, int b);
void			get_textures(t_map *map, t_graph *gr);
int				what_texture(t_graph *gr);
double			calcul_texture(t_graph *gr);
void			draw_wall(t_map *map, t_graph *gr, int x);
int				keyrelease(int key, t_graph *gr);
int				keypress(int key, t_graph *gr);
int				moove(t_graph *gr);
int				is_wall(t_graph *gr, t_map *map);
void			look_right(t_graph *gr, double tmp_dirx, double tmp_planecamx);
void			look_left(t_graph *gr, double tmp_dirx, double tmp_planecamx);
int				update(t_graph *gr);
void			left_or_right(t_graph *gr);
void			up_or_down(t_graph *gr);
void			moove_left_right(t_graph *gr);
void			moove_up_down(t_graph *gr);
void			hub_sprite(t_map *map, t_graph *gr);
void			calcdraw_sprite(t_graph *gr, t_map *map);
int				exitred(t_graph *gr, int flag);
void			savemode(t_map *map, t_graph *gr);
void			draw_sprite(t_graph *gr, int startx, t_map *map);
void			error(t_map *map, unsigned long flag, t_vector *vct);
int				gestion_parser(int ret, t_vector *line, t_map *map,
									t_state_machine *machine);
void			pos(t_graph *gr, size_t x, size_t y);
int				is_posy_into_wall(t_graph *gr, t_map *map);
int				is_posx_into_wall(t_graph *gr, t_map *map);

#endif
