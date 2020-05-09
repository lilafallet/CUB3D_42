/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 20:41:48 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/09 20:41:47 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FAILURE
#  define FAILURE -1
# endif

# define LEN_ZERO 1

# define VOID_LINE 10

# define ERROR 2
# define NEXT 4
# define NEXT_OTHERCHAR 6

# define CHAR_RESOLUTION 'R'
# define STR_TEXTURE_NO "NO"
# define STR_TEXTURE_SO "SO"
# define STR_TEXTURE_WE "WE"
# define STR_TEXTURE_EA "EA"
# define STR_MAP "012NSWE \t"
# define STR_TEXTURE "NOSOWEEA"
# define FIRST_TEXTURE "NSWE"
# define STR_RESOLUTION "R"
# define CHAR_WALL '1'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

# define SPACE ' '
# define TAB '\t'
# define PATH "./"
# define SIZE_PATH 2
# define SLASH '/'
# define PLUS '+'
# define COMMA ','
# define NB_COMMA 2

# define BT_NO 			0x0000001
# define BT_SO 			0x0000002
# define BT_WE 			0x0000004
# define BT_EA 			0x0000008
# define BT_SPR			0x0000010
# define BT_RESOLUTION	0x0000100
# define BT_COLOR_F		0x0001000
# define BT_COLOR_C		0x0002000

# define ALL_INFO		0x000311f

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

# define IS_ERROR										0xFFF000000
# define NB_ERROR			12
# define ERR_ARG			0
# define ERR_GLOBAL			1
# define ERR_SAVE			2
# define ERR_FORMAT			3
# define ERROR_RESOLUTION_NUMBER_ARGUMENTS				0x001000000
# define ERROR_TEXTURE_NUMBER_ARGUMENTS					0x002000000
# define ERROR_COLOR_WRONG_TYPE_NUMBER					0x004000000
# define ERROR_COLOR_NUMBER_COLOR_ARGUMENTS				0x008000000
# define ERROR_COLOR_NUMBER_ARGUMENTS					0x010000000
# define ERROR_COLOR_ALREADY							0x020000000
# define ERROR_MAP_NOT_VALID							0x040000000
# define ERROR_RESOLUTION_WRONG_TYPE_NUMBER				0x080000000
# define ERROR_RESOLUTION_WRONG_TYPE_INDICATOR			0x100000000
# define ERROR_TEXTURE_ALREADY							0x200000000
# define ERROR_COLOR_NOT_NUMBER							0x400000000
# define ERROR_TEXTURE_FORMAT							0x800000000

# define ERR1				"RESOLUTION : too much information\n"
# define ERR2				"TEXTURE = too much information\n"
# define ERR3				"COLOR = wrong type of number\n"
# define ERR4				"COLOR = number of color is invalid\n"
# define ERR5				"COLOR = too much information\n"
# define ERR6				"COLOR = alreagraph->recup.dy have color\n"
# define ERR7				"MAP = invalid map\n"
# define ERR8				"RESOLUTION = wrong type of number\n"
# define ERR9				"RESOLUTION = wrong type of indicator\n"
# define ERR10				"TEXTURE = alreagraph->recup.dy have texture\n"
# define ERR11				"COLOR = the argument is not a number\n"
# define ERR12				"TEXTURE = no path to the texture\n"
# define ERROR_ARGUMENTS "ARGUMENTS :programme affiche image dans une fenetre\n"
# define ERROR_STR_GLOBAL "one line is invalid\n"
# define ERROR_ARGUMENT_SAVE "SAVE :sauver premiere image rendue format bmp\n"
# define ERROR_ARGUMENT_FORMAT "ARGUMENTS : wrong format (expecting .cub)\n"

# define STRING_CHECK_R		"SFCNSEW"
# define STRING_SPACE_TAB " \t"

# define BUFFER_SIZE 4096

# define NB_TEXTURE 5
# define NB_STATE 4
# define NB_COLOR 3
# define NB_RESOLUTION 2
# define NB_POSITION_MAP 1
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S 4
# define NB_INDIC_COLOR 2
# define NB_INFO 4
# define NB_DIFF_COLOR 4
# define DIFF_LEN_COLOR 5
# define IND_R_COLOR 0
# define IND_NO_COLOR 1
# define IND_SO_COLOR 2
# define IND_WE_COLOR 3
# define NB_DIFF_MAP_STR 4
# define NB_DIFF_MAP_C 4
# define DIFF_LEN_MAP 9
# define IND_NO_MAP 0
# define IND_SO_MAP 1
# define IND_WE_MAP 2
# define IND_EA_MAP 3
# define IND_S_MAP 4
# define IND_R_MAP 5
# define IND_F_MAP 6
# define IND_C_MAP 7
# define WAY_WALL_SPRITE 3
# define OUTMAP 6
# define AXE_X 0
# define AXE_Y 1
# define FIRST_CHAR 0
# define NB_DIFF_RESOL 5
# define DIFF_LEN_RESOL 6
# define IND_NO_RESOL 0
# define IND_SO_RESOL 1
# define IND_WE_RESOL 2
# define IND_F_RESOL 3
# define IND_C_RESOL 4
# define R 0
# define G 1
# define B 2

# define COLOR_C 0
# define COLOR_F 1

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <limits.h>

enum			e_state
{
	RESOLUTION,
	TEXTURE,
	COLOR,
	MAP
};

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

typedef struct	s_f_info
{
	unsigned long	resolution_x;
	unsigned long	resolution_y;
}				t_f_info;

typedef struct	s_recup
{
	int				resolution[NB_RESOLUTION];
	int				posx;
	int				posy;
	char			dirpos;
	char			*str_texture[NB_TEXTURE];
	char			*str_text_spr;
	char			*str_text_no;
	char			*str_text_so;
	char			*str_text_we;
	char			*str_text_ea;
	int				tab_color_f[NB_COLOR];
	int				tab_color_c[NB_COLOR];
	enum e_map		**tab_map;
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

}				t_utils;

typedef struct	s_state_machine
{
	enum e_state		state;
	unsigned long		info;
	char				pad[4];
}				t_state_machine;

typedef struct	s_map
{
	t_recup			recup;
	t_utils			utils;
}				t_map;

typedef struct	s_recupg
{
	void			*mlx_ptr;
	void			*img_ptr;
	int				*data;
	unsigned long	img_color;
	void			*win_ptr;
	int				size_line;
	int				bits;
	int				endian;
}				t_recupg;

typedef struct	s_utilsg
{
	int				color_total_f;
	int				r_f;
	int				g_f;
	int				b_f;
	int				color_total_c;
	int				color1_c;
	int				color2_c;
	int				color3_c;
	int				img_x;
	int				img_y;
	int				pos_x;
	int				pos_y;
	int				size_x;
	int				size_y;
}				t_utilsg;

typedef struct	s_graph
{
	t_recupg	recup;
	t_utilsg	utils;
}				t_graph;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_set_coord
{
	t_coord		start;
	t_coord		end;
}				t_set_coord;

typedef struct	s_rting
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	time;
	double	oldtime;
	double	camx;
	double	camy;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidex;
	double	sidey;
	double	distx;
	double	disty;
	double	perspwall;
	int		incrx;
	int		incry;
	int		hit;
	int		what_side;
	int		size_heightline;
	int		startline;
	int		endline;
	int		color_north;
	int		color_south;
	int		color_west;
	int		color_east;
	int		color_wall;
}				t_rting;

# define	ACCESS	NULL

typedef	int	(*t_function)(t_vector *, t_map *, t_state_machine *);

int				hub_verification_map(t_state_machine *machine, t_vector *line,
										unsigned long nb_line);
void			ft_free(t_map *map, t_vector *line);
int				first_parser(t_map *map, int fd, t_state_machine *machine);
void			printf_errors(unsigned long flag, unsigned long line);
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
							char *tab_color[NB_INDIC_COLOR]);
int				init_machine_color(uint8_t count, t_state_machine *machine,
									t_vector *cp);
void			is_texture(uint8_t *count, t_vector *split,
							t_state_machine *machine,
							char *tab_texture[NB_TEXTURE]);
void			recuperation_texture(t_state_machine *machine, uint8_t count,
										t_vector *split, t_map *map);
void			is_indic_resolution(t_vector *split, t_state_machine *machine);
void			is_number_resolution(t_vector *split, t_state_machine *machine,
										size_t i, t_map *map);
int				what_second_argument(char *argument);
int				is_good_file(char *str);
int				true_or_false(t_vector *split, t_vector *vct, uint8_t count,
								t_state_machine *machine);
size_t			fill_line(t_map *map, enum e_map **cpy_tab);
t_state_machine	*get_state_machine(t_state_machine *machine);
void			start_graph(t_map *map);
t_map			*get_map(t_map *map);
t_graph			*graph_holder(t_graph *graph);
void			init_graph(t_graph *graph, t_map *map);
void			process_window(t_graph *graph, t_map *map);
void			init_raycasting(t_map *map, t_rting *rting);
void			process_raycasting(t_map *map, t_rting *rting, t_graph *graph);

#endif
