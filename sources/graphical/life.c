/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:14:46 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/17 14:54:41 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	life(t_graph *gr, t_map *map) //BONUS
{
	size_t	y;
	size_t	x;

	if (gr->lf.count == 14)
	{
		//exitred(gr);
	}
	if (gr->lf.count_outsprite == 1)
	{
		gr->lf.count++;	
	}
	printf("count = %d\n", gr->lf.count); //
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
	if (gr->lf.count == 0)
		gr->lf.startx_sprite = 250;
	if (gr->lf.count > 0 && gr->lf.count_outsprite == 1)
		gr->lf.tmp_startx_sprite = gr->lf.startx_sprite - 15;
	if (gr->lf.count > 0 && gr->lf.count_outsprite == 0)
		gr->lf.startx_sprite = gr->lf.tmp_startx_sprite;
	while (y < gr->lf.endy)
	{
		x = gr->lf.startx;
		while (x < gr->lf.endx)
		{
			gr->win.data[y * map->recup.resolution[AXE_X] + x] = 0x228B22;
			if (((gr->lf.firstx == TRUE || gr->lf.firsty == TRUE)
					&& x > gr->lf.startx_sprite
					&& x <= gr->lf.endx_sprite))
			{
				//PERTE DE VIE
				gr->win.data[y * map->recup.resolution[AXE_X] + x] = 0xFF0000;
			}
			if (x < gr->lf.width_outxleft || x > gr->lf.width_outxright ||
					y < gr->lf.width_outyup || y > gr->lf.width_outydown)
			{	
				//CONTOUR
				gr->win.data[y * map->recup.resolution[AXE_X] + x] = 0xFFFFFF;
			}
			x++;
		}
		y++;
	}
}
