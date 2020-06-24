/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:45:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 14:31:53 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_draw_wall(t_graph *gr, int who)
{
	if (gr->rting.side == EA || gr->rting.side == WE)
		gr->text.wallhit = gr->rting.posy + gr->rting.perpwalldist
							* gr->rting.raydiry;
	else
		gr->text.wallhit = gr->rting.posx + gr->rting.perpwalldist
							* gr->rting.raydirx;
	gr->text.wallhit -= floor(gr->text.wallhit);
	gr->text.texx = (int)(gr->text.wallhit * (double)gr->text.size[who][WIDTH]);
}

void		draw_wall(t_map *map, t_graph *gr, int x)
{
	int		y;
	int		who;

	who = what_texture(gr);
	init_draw_wall(gr, who);
	y = gr->draw.start;
	if ((gr->rting.side == NO || gr->rting.side == SO) && gr->rting.raydiry > 0)
		gr->text.texx = gr->text.size[who][WIDTH] - gr->text.texx - 1;
	if ((gr->rting.side == WE || gr->rting.side == EA) && gr->rting.raydirx < 0)
		gr->text.texx = gr->text.size[who][WIDTH] - gr->text.texx - 1;
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
	if (y < 0)
		y = 0;
	floor_color = get_rgb(map->recup.tab_color_f[R], map->recup.tab_color_f[G],
							map->recup.tab_color_f[B]);
	while (y >= gr->draw.end)
	{
		gr->win.data[y * map->recup.resolution[AXE_X] + x] = floor_color;
		y--;
	}
}

static void	draw_sky(t_map *map, t_graph *gr, int x)
{
	int	y;
	int	sky_color;
	int	axe_x;

	y = 0;
	axe_x = map->recup.resolution[AXE_X];
	sky_color = get_rgb(map->recup.tab_color_c[R], map->recup.tab_color_c[G],
							map->recup.tab_color_c[B]);
	while (y < gr->draw.start && y < map->recup.resolution[AXE_Y])
	{
		gr->win.data[y * axe_x + x] = sky_color;
		y++;
	}
}

void		hub_draw(t_map *map, t_graph *gr, int x)
{
	draw_floor(map, gr, x);
	draw_sky(map, gr, x);
}
