/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:45:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/16 12:00:31 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_map *map, t_graph *gr, int x)
{
	int		y;
	int		who;

	who = what_texture(gr);
	if (gr->rting.side == 0)
			gr->text.wallx = gr->rting.posy + gr->rting.perpwalldist
								* gr->rting.raydiry;
	else
			gr->text.wallx = gr->rting.posx + gr->rting.perpwalldist
								* gr->rting.raydirx;
	gr->text.wallx -= floor(gr->text.wallx);
	gr->text.texx = gr->text.wallx * (double)gr->text.size[who][WIDTH];
	y = gr->draw.start;
	while (y < gr->draw.end)
	{
		gr->text.texy = (y - map->recup.resolution[AXE_Y] / 2
							+ gr->draw.height_line / 2)
							* gr->text.size[who][HEIGHT] / gr->draw.height_line;
		gr->win.data[x + y * (gr->win.size_line / 4)] =
						gr->text.data[who][gr->text.texx + gr->text.texy
						* gr->text.size[who][WIDTH]];
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
	while (y >= gr->draw.end)
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
	while (y < gr->draw.start)
	{
		gr->win.data[y * map->recup.resolution[AXE_X] + x] = sky_color; //BLEU CIEL
		y++;
	}
}

void	shadow_wall(t_graph *gr)
{
	gr->color.south = 0x0066CC; //BLUE
	gr->color.north = 0x990000; //RED
	gr->color.east = 0xFFD700; //YELLOW
	gr->color.west = 0x009900; //GREEN
	
	if (gr->rting.side == 0 && gr->rting.raydirx > 0)
		gr->color.wall = gr->color.north; //ombre
	else if (gr->rting.side == 0 && gr->rting.raydirx < 0)
		gr->color.wall = gr->color.south;	//ombre
	else if (gr->rting.side == 1 && gr->rting.raydiry > 0)
		gr->color.wall = gr->color.east;	//ombre
	else
		gr->color.wall = gr->color.west;	//ombre
}

void	hub_draw(t_map *map, t_graph *gr, int x)
{
	draw_floor(map, gr, x);
	draw_sky(map, gr, x);
}
