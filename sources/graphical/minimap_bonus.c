/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:16:52 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:16:53 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		get_element_color(t_graph *gr, t_map *map,
						const int offset_x, const int offset_y)
{
	const int			colors[] = {GREY, BLUE, GREEN, GREY, BLACK,
										BLACK, BLACK};
	const int			x = ((int)gr->rting.posx + offset_x);
	const int			y = ((int)gr->rting.posy + offset_y);

	if (x < 0 || y < 0
		|| x >= (int)map->utils.max_index || y >= (int)map->utils.max_line)
		return (BLACK);
	if (offset_x == 0 && offset_y == 0)
		return (RED);
	return (colors[map->recup.tab_map[y][x]]);
}

static void		get_map_size(t_graph *gr)
{
	t_map		*map;

	if (gr->minmap.max_size == UNDEFINED)
	{
		if (gr->win.max_screen_width > gr->win.max_screen_height)
		{
			gr->minmap.max_size = gr->win.max_screen_width;
			if (gr->win.max_screen_height * (16.0 / 9.0) < gr->minmap.max_size)
				gr->minmap.max_size = (int)((float)gr->win.max_screen_height
								* (16.0 / 9.0));
		}
		else
		{
			gr->minmap.max_size = gr->win.max_screen_height;
			if (gr->win.max_screen_width * (9.0 / 16.0) < gr->minmap.max_size)
				gr->minmap.max_size = (int)((float)gr->win.max_screen_width
								* (9.0 / 16.0));
		}
		map = get_map(NULL);
		if (map->recup.resolution[AXE_X] > map->recup.resolution[AXE_Y])
			gr->minmap.width = map->recup.resolution[AXE_X];
		else
			gr->minmap.width = map->recup.resolution[AXE_Y];
	}
}

static int		get_case_size(t_graph *gr)
{
	static int	case_size = UNDEFINED;
	int			case_max_size;
	static int	max_size = UNDEFINED;
	static int	width = UNDEFINED;

	case_max_size = CASE_MAX_SIZE > CASE_MAX_SIZE || CASE_MAX_SIZE
					< CASE_MIN_SIZE ? CASE_MAX_SIZE : CASE_MAX_SIZE;
	gr->minmap.max_size = max_size;
	gr->minmap.width = width;
	get_map_size(gr);
	if (case_size != UNDEFINED)
		return (case_size);
	case_size = gr->minmap.width * case_max_size / gr->minmap.max_size;
	if (case_size < CASE_MIN_SIZE)
		case_size = CASE_MIN_SIZE;
	else if (case_size > CASE_MAX_SIZE)
		case_size = CASE_MAX_SIZE;
	return (case_size);
}

static void		fill_minimap_case(const int offset_x, const int offset_y,
						t_graph *gr, t_map *map)
{
	const int	color = get_element_color(gr, map, offset_x, offset_y);
	int			y;
	int			x;
	int			i;
	int			j;

	y = get_init_offset(map->recup.resolution[AXE_Y], gr->win.max_screen_height)
						+ offset_y * get_case_size(gr);
	x = map->recup.resolution[AXE_X]
		- get_init_offset(map->recup.resolution[AXE_X],
		gr->win.max_screen_width) + offset_x * get_case_size(gr);
	i = 0;
	if (y < 0 || x < 0)
		return ;
	while (i < get_case_size(gr))
	{
		j = 0;
		while (j < get_case_size(gr))
		{
			gr->win.data[(y + i) * map->recup.resolution[AXE_X]
							+ (x + j)] = get_final_color(i, j, color);
			j++;
		}
		i++;
	}
}

void			minimap(t_map *map, t_graph *gr)
{
	int		offset_x;
	int		offset_y;

	offset_y = PLAYER_POS - MID_NB_MAP;
	while (offset_y <= MID_NB_MAP)
	{
		offset_x = PLAYER_POS - MID_NB_MAP;
		while (offset_x <= MID_NB_MAP)
		{
			fill_minimap_case(offset_x, offset_y, gr, map);
			offset_x++;
		}
		offset_y++;
	}
}
