/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 20:41:48 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/14 15:32:37 by lfallet          ###   ########.fr       */
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

# define ERROR 2
# define NEXT 4
# define NO_CHAR 5

# define CHAR_RESOLUTION 'R'
# define STR_TEXTURE_NO "NO"
# define STR_TEXTURE_SO "SO"
# define STR_TEXTURE_WE "WE"
# define STR_TEXTURE_EA "EA"
# define STR_TEXTURE_SPR "S"
# define CHAR_TEXTURE_SPR 'S'
# define STR_COLOR "FC"
# define CHAR_F_COLOR 'F'
# define CHAR_C_COLOR 'C'
# define STR_MAP "012NSWE"
# define STR_TEXTURE "NOSOWEEA"
# define FIRST_TEXTURE "NSWE"

# define SPACE ' '
# define TAB '\t'
# define PATH "./"
# define SIZE_PATH 2
# define DOT '.'
# define SLASH '/'
# define PLUS '+'
# define COMMA ','
# define INDEX_TEXTURE 2

# define ERROR_ARGUMENTS "Error of arguments: OUVRIR FENETRE(lire pdf)\n\n"
# define WRONG_INFORMATIONS "Wrong informations : REGARDER QUOI FAIRE\n\n"

# define BT_NO 	0x0000001
# define BT_SO 	0x0000002
# define BT_WE 	0x0000004
# define BT_EA 	0x0000008
# define BT_SPR 0x0000010

# define BT_RESOLUTION 0x0000100
# define BT_COLOR_F 0x0001000
# define BT_COLOR_C 0x0002000
# define BT_F_RED 0x0004000
# define BT_F_GREEN 0x0008000
# define BT_F_BLUE 0x0010000
# define BT_C_RED 0x0020000
# define BT_C_GREEN 0x0040000
# define BT_C_BLUE 0x0080000
# define BT_POSITION_N 0x0100000
# define BT_POSITION_S 0x0200000
# define BT_POSITION_W 0x0400000
# define BT_POSITION_E 0x0800000

# define IS_ERROR			0x0FF000000
# define NB_ERROR			8
# define ERR_USAGE			0
# define ERROR_RESOLUTION	0x001000000
# define ERROR_TEXTURE		0x002000000
# define ERROR_COLOR		0x004000000
# define ERROR_MAP			0x008000000
# define ERROR_NO			0x010000000
# define ERROR_SO			0x020000000
# define ERROR_WE			0x040000000
# define ERROR_EA			0x080000000

# define ERR1				"Wrong resolution = voir ce qu'il faut faire\n"
# define ERR2				"Wrong texture = voir ce qu'il faut faire\n"
# define ERR3				"Wrong color = voir ce qu'il faut faire\n"
# define ERR4				"Bad map = voir ce qu'il faut faire\n"

# define STRING_CHECK_R		"SFCNSEW"

# define BUFFER_SIZE 4096

# define NB_TEXTURE 5
# define NB_STATE 4
# define NB_COLOR 3
# define NB_RESOLUTION 2
# define ALL 5
# define NB_POSITION_MAP 1

# define INDEX_RESOLUTION_X 0
# define INDEX_RESOLUTION_Y 1

# define MINUS '-'

# define COLOR_C 1
# define COLOR_F 2

# include "libft.h"

enum			e_state
{
	RESOLUTION, /*0*/
	TEXTURE, /*1*/
	COLOR, /*3*/
	MAP /*4*/
};

typedef struct	st_f_info
{
	unsigned long	resolution_x;
	unsigned long	resolution_y;
}				t_f_info;

typedef struct	s_info
{
	size_t			index_map;
	char			*str_texture[NB_TEXTURE];
	char			*str_resolution[NB_RESOLUTION];
	char			*str_text_spr;
	char			*str_text_no;
	char			*str_text_so;
	char			*str_text_we;
	char			*str_text_ea;
	char			*str_color_f[NB_COLOR];
	char			*str_color_c[NB_COLOR];
	char			*str_map[BUFFER_SIZE];
	char			str_position[NB_POSITION_MAP];
	char			pad[7];
}				t_info;

typedef struct	s_state_machine
{
	char				*str_info_final;
	char				*str_tmp_info_final;
	unsigned long		information;
	struct s_info		info;
	struct st_f_info	final_info;
	enum e_state		state;
	char				pad[4];
}				t_state_machine;

typedef	int	(*t_function)(t_vector *, t_state_machine *);

int				main(int ac, char **av);
int				hub_verification_map(t_state_machine *machine, t_vector *line,
										unsigned long nb_line);
void			ft_free(t_state_machine *machine, t_vector *line);
int				first_parser(t_state_machine *machine, t_vector *line);
void			printf_errors(unsigned long flag, unsigned long line);
int				split_resolution(t_vector *resol, char **str_resolution,
									t_vector *vct);
int				is_next_or_error_resolution(t_vector *vct);
int				is_resolution(t_vector *resol, t_vector *vct);
int				init_machine_resolution(t_state_machine *machine, int ret);
int				is_texture(t_vector *vct, char **tab_texture);
void			what_bitwaze(t_state_machine *machine, int index);
int				pre_process_split(t_vector *texture, t_vector *vct,
									char *str_texture);
int				process_texture(int ret, t_vector *vct, char **tab_texture);
int				clean_before(t_vector *vct, char **str_texture, int index);
int				process_texture(int ret, t_vector *vct, char **tab_texture);
void			init_machine_texture(int ret, t_state_machine *machine,
										int index, t_vector *vct);

#endif
