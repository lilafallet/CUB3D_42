/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:23:14 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 17:38:11 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	colorisation_sprite(t_graph *gr, int starty, int startx, t_map *map)
{
	gr->sp.color = ((int *)gr->text.data[S])[gr->sp.textw * gr->sp.texty
						+ gr->sp.textx];
	if ((gr->sp.color & 0xFFFFFF) != 0)
	{
		gr->win.data[starty * map->recup.resolution[AXE_X]
						+ startx] = gr->sp.color;
	}
}

void		draw_sprite(t_graph *gr, int startx, t_map *map)
{
	int	tmp_starty;
	int	dim;

	gr->sp.textx = (int)(PIXEL * (startx - (-gr->sp.width / 2
						+ gr->sp.screen_where))
						* gr->text.size[S][WIDTH]
						/ gr->sp.width / PIXEL);
	if (gr->sp.playposy > 0 && startx >= 0
		&& startx < map->recup.resolution[AXE_X]
		&& gr->sp.playposy < gr->sp.raybuff[startx])
	{
		tmp_starty = gr->sp.starty;
		gr->sp.textw = gr->text.size[S][WIDTH];
		while (tmp_starty < gr->sp.endy)
		{
			dim = tmp_starty * PIXEL - map->recup.resolution[AXE_Y]
					* PIXEL_DIV2 + gr->sp.height * PIXEL_DIV2;
			gr->sp.texty = ((dim * gr->text.size[S][HEIGHT] / gr->sp.height)
								/ PIXEL);
			colorisation_sprite(gr, tmp_starty, startx, map);
			tmp_starty++;
		}
	}
}

void		calcdraw_sprite(t_graph *gr, t_map *map)
{
	gr->sp.height = labs((long)(map->recup.resolution[AXE_Y]
						/ gr->sp.playposy));
	gr->sp.starty = -gr->sp.height / 2 + map->recup.resolution[AXE_Y] / 2;
	if (gr->sp.starty < 0)
		gr->sp.starty = 0;
	gr->sp.endy = gr->sp.height / 2 + map->recup.resolution[AXE_Y] / 2;
	if (gr->sp.endy >= map->recup.resolution[AXE_Y])
		gr->sp.endy = map->recup.resolution[AXE_Y] - 1;
	gr->sp.width = fabs(map->recup.resolution[AXE_Y] / gr->sp.playposy);
	gr->sp.startx = -gr->sp.width / 2 + gr->sp.screen_where;
	if (gr->sp.startx < 0)
		gr->sp.startx = 0;
	gr->sp.endx = gr->sp.width / 2 + gr->sp.screen_where;
	if (gr->sp.endx >= map->recup.resolution[AXE_X])
		gr->sp.endx = map->recup.resolution[AXE_X];
}
