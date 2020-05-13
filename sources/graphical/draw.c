/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:45:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/13 16:18:17 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;

	y = rting->start_draw;
	while (y < rting->end_draw)
	{
		graph->recup.data[y * map->recup.resolution[AXE_X] + x]
							= rting->color_wall;
		y++;	
	}
}

static void	draw_floor(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;
	int	floor_color;

	y = map->recup.resolution[AXE_Y] - 1;
	floor_color = get_rgb(map->recup.tab_color_f[R], map->recup.tab_color_f[G],
							map->recup.tab_color_f[B]); 
	while (y >= rting->end_draw)
	{
		graph->recup.data[y * map->recup.resolution[AXE_X] + x] = floor_color; //MARRON
		y--;
	}
}

static void	draw_sky(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;
	int	sky_color;
	
	y = 0;
	sky_color = get_rgb(map->recup.tab_color_c[R], map->recup.tab_color_c[G],
							map->recup.tab_color_c[B]); 
	while (y < rting->start_draw)
	{
		graph->recup.data[y * map->recup.resolution[AXE_X] + x] = sky_color; //BLEU CIEL
		y++;
	}
}

static void	color_wall(t_map *map, t_graph *graph, t_rting *rting)
{
	rting->color_south = 0x0066CC; //BLUE
	rting->color_north = 0x990000; //RED
	rting->color_east = 0xFFD700; //YELLOW
	rting->color_west = 0x009900; //GREEN
	
	if (rting->side == 0 && rting->raydirx > 0)
		rting->color_wall = rting->color_north;
	else if (rting->side == 0 && rting->raydirx < 0)
		rting->color_wall = rting->color_south;	
	else if (rting->side == 1 && rting->raydiry > 0)
		rting->color_wall = rting->color_east;	
	else
		rting->color_wall = rting->color_west;	
}

void	hub_draw(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	color_wall(map, graph, rting);
	draw_wall(map, graph, rting, x);
	draw_floor(map, graph, rting, x);
	draw_sky(map, graph, rting, x);
}
