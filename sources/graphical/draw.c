/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:45:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/14 15:41:40 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall(t_map *map, t_graph *gr, int x)
{
	int	y;

	y = gr->draw.start_draw;
	while (y < gr->draw.end_draw)
	{
		gr->win.data[y * map->recup.resolution[AXE_X] + x]
							= gr->color.color_wall;
		y++;	
	}
}

static void	draw_floor(t_map *map, t_graph *gr, int x)
{
	int	y;
	int	floor_color;

	y = map->recup.resolution[AXE_Y] - 1;
	floor_color = get_rgb(map->recup.tab_color_f[R], map->recup.tab_color_f[G],
							map->recup.tab_color_f[B]); 
	while (y >= gr->draw.end_draw)
	{
		gr->win.data[y * map->recup.resolution[AXE_X] + x] = floor_color; //MARRON
		y--;
	}
}

static void	draw_sky(t_map *map, t_graph *gr, int x)
{
	int	y;
	int	sky_color;
	
	y = 0;
	sky_color = get_rgb(map->recup.tab_color_c[R], map->recup.tab_color_c[G],
							map->recup.tab_color_c[B]); 
	while (y < gr->draw.start_draw)
	{
		gr->win.data[y * map->recup.resolution[AXE_X] + x] = sky_color; //BLEU CIEL
		y++;
	}
}

void	shadow_wall(t_map *map, t_graph *gr)
{
	gr->color.color_south = 0x0066CC; //BLUE
	gr->color.color_north = 0x990000; //RED
	gr->color.color_east = 0xFFD700; //YELLOW
	gr->color.color_west = 0x009900; //GREEN
	
	if (gr->rting.side == 0 && gr->rting.raydirx > 0)
		gr->color.color_wall = gr->color.color_north; //ombre
	else if (gr->rting.side == 0 && gr->rting.raydirx < 0)
		gr->color.color_wall = gr->color.color_south;	//ombre
	else if (gr->rting.side == 1 && gr->rting.raydiry > 0)
		gr->color.color_wall = gr->color.color_east;	//ombre
	else
		gr->color.color_wall = gr->color.color_west;	//ombre
}

void	hub_draw(t_map *map, t_graph *gr, t_graph *gr, int x)
{
	draw_wall(map, gr, gr, x);
	draw_floor(map, gr, gr, x);
	draw_sky(map, gr, gr, x);
}
