/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:22:54 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 12:19:05 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycasting(t_map *map, t_graph *gr, int x)
{
	gr->rting.camerax = 2 * x / (double)map->recup.resolution[AXE_X] - 1;
	gr->rting.raydirx = gr->rting.dirx + gr->rting.planecamx
							* gr->rting.camerax;
	gr->rting.raydiry = gr->rting.diry + gr->rting.planecamy
							* gr->rting.camerax;
	gr->rting.mapx = (int)gr->rting.posx;
	gr->rting.mapy = (int)gr->rting.posy;

	gr->rting.deltadistx = fabs(1 / gr->rting.raydirx);
	gr->rting.deltadisty = fabs(1 / gr->rting.raydiry);
}

static void	init_step_distray(t_graph *gr)
{
	if (gr->rting.raydirx < 0)
	{	
		gr->rting.stepx = -1;
		gr->rting.distx = (gr->rting.posx - gr->rting.mapx)
							* gr->rting.deltadistx;
	}
	else
	{
		gr->rting.stepx = 1;
		gr->rting.distx = (gr->rting.mapx + 1.0 - gr->rting.posx)
							* gr->rting.deltadistx;
	}
	if (gr->rting.raydiry < 0)
	{
		gr->rting.stepy = -1;
		gr->rting.disty = (gr->rting.posy - gr->rting.mapy)
							* gr->rting.deltadisty;
	}
	else
	{
		gr->rting.stepy = 1;
		gr->rting.disty = (gr->rting.mapy + 1.0 - gr->rting.posy)
							* gr->rting.deltadisty;
	}
}

static void	check_wall(t_map *map, t_graph *gr)
{
	gr->rting.hit = 0;
	while (gr->rting.hit == 0)
	{
		if (gr->rting.distx < gr->rting.disty)
		{
			gr->rting.distx += gr->rting.deltadistx;
			gr->rting.mapx += gr->rting.stepx;
			gr->rting.side = gr->rting.stepx == 1 ? EA : WE;
		}
		else
		{
			gr->rting.disty += gr->rting.deltadisty;
			gr->rting.mapy += gr->rting.stepy;
			gr->rting.side = gr->rting.stepy == 1 ? SO : NO;
		}
		if (map->recup.tab_map[gr->rting.mapy][gr->rting.mapx] == 1)
			gr->rting.hit = 1;
	} 
}

static void	calcul_draw(t_map *map, t_graph *gr)
{
	gr->draw.height_line = (int)(map->recup.resolution[AXE_Y]
			/ gr->rting.perpwalldist);
	gr->draw.start = -gr->draw.height_line / 2
							+ map->recup.resolution[AXE_Y] / 2;
	if (gr->draw.start < 0)
		gr->draw.start = 0;
	gr->draw.end = gr->draw.height_line / 2
							+ map->recup.resolution[AXE_Y] / 2;
	if (gr->draw.end >= map->recup.resolution[AXE_Y])
		gr->draw.end = map->recup.resolution[AXE_Y] - 1;
	else if (gr->draw.end < 0)
		gr->draw.end = 0;
}

void	start_raycasting(t_map *map, t_graph *gr)
{
	int	x;

	x = 0;
	while (x < map->recup.resolution[AXE_X])
	{
		init_raycasting(map, gr, x);
		init_step_distray(gr);
		check_wall(map, gr);
		if (gr->rting.side == EA || gr->rting.side == WE)
			gr->rting.perpwalldist = (gr->rting.mapx - gr->rting.posx
					+ (1 - gr->rting.stepx) / 2) / gr->rting.raydirx;
		else

			gr->rting.perpwalldist = (gr->rting.mapy - gr->rting.posy
					+ (1 - gr->rting.stepy) / 2) / gr->rting.raydiry;
		calcul_draw(map, gr);
		gr->sp.raybuff[x] = gr->rting.perpwalldist;
		draw_wall(map, gr, x);
		hub_draw(map, gr, x);
		x++;
		gr->draw.no_sky = FALSE;
	}
}
