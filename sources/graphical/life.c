/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:14:46 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/17 12:28:23 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	life(t_graph *gr, t_map *map) //BONUS
{
	size_t	y;
	size_t	x;

	gr->lf.starty = 50;
	y = gr->lf.starty;
	gr->lf.endy = 110;
	gr->lf.endx = 270;
	gr->lf.startx = 60;
	gr->lf.width_outxleft = 65;
	gr->lf.width_outxright = 265;
	gr->lf.width_outyup = 55;
	gr->lf.width_outydown = 105;
	gr->lf.endx_sprite = 265;
	gr->lf.startx_sprite = 250;
	while (y < gr->lf.endy)
	{
		x = gr->lf.startx;
		while (x < gr->lf.endx)
		{
			if (x < gr->lf.width_outxleft || x > gr->lf.width_outxright ||
					y < gr->lf.width_outyup || y > gr->lf.width_outydown)
			{	
				gr->win.data[y * map->recup.resolution[AXE_X] + x] = 0xFFFFFF;
			}
			else
			{
				if (gr->lf.is_sprite = TRUE && x > gr->lf.startx_sprite
					&& x <= gr->lf.endx_sprite)
				{
					
					gr->win.data[y * map->recup.resolution[AXE_X] + x] = 0xFF0000;
				}
				else
				{
					gr->win.data[y * map->recup.resolution[AXE_X] + x] = 0x228B22;

				}
			}
			x++;
		}
		y++;
	}
}
