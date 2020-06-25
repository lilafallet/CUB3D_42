/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:16:43 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:16:44 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	restart_mode(int key, t_graph *gr, t_map *map)
{
	if (key == K_RESTART && (gr->mv.log & RESTART) == FALSE)
	{
		gr->mv.log |= RESTART;
		gr->lf.count = 0;
		gr->rting.dirx = 0;
		gr->rting.diry = 0;
		gr->rting.planecamx = 0;
		gr->rting.planecamy = 0;
		gr->lf.count_outsprite = FALSE;
		gr->lf.startx_sprite = 250;
		gr->lf.old = 0;
		free(gr->sp.raybuff);
		init_map(map, gr);
	}
}

void	screen_life(t_graph *gr, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->recup.resolution[AXE_Y])
	{
		x = 0;
		while (x < map->recup.resolution[AXE_X])
		{
			if (y <= LIFE150 || y >= map->recup.resolution[AXE_Y] - LIFE150)
				gr->win.data[y * map->recup.resolution[AXE_X] + x] = RED;
			if (y > LIFE150 && y < map->recup.resolution[AXE_Y] - LIFE150
					&& x <= LIFE100)
				gr->win.data[y * map->recup.resolution[AXE_X] + x] = RED;
			if (y > LIFE150 && y < map->recup.resolution[AXE_Y] - LIFE150
					&& x >= map->recup.resolution[AXE_X] - LIFE100)
				gr->win.data[y * map->recup.resolution[AXE_X] + x] = RED;
			x++;
		}
		y++;
	}
}

void	screen_dead(t_graph *gr, t_map *map, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->recup.resolution[AXE_Y])
	{
		x = 0;
		while (x < map->recup.resolution[AXE_X])
		{
			gr->win.data[y * map->recup.resolution[AXE_X] + x] = color;
			x++;
		}
		y++;
	}
}
