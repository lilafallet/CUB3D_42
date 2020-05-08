/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:30:22 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/09 00:26:14 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_position_direction(t_map *map, t_rting *rting, int x)
{
	rting->camx = (2 * x) / map->recup.resolution[AXE_X] - 1;
	rting->raydirx = rting->dirx + (rting->planex * rting->camx);
	rting->raydiry = rting->diry + (rting->planey * rting->camy);
}

void	len_ray(t_rting *rting)
{
	rting->distx = rting->diry == 0 ? 0
					: ((rting->raydirx == 0) ? 1
					: ft_abs(1 / rting->raydirx));
	rting->disty = rting->dirx == 0 ? 0
					: ((rting->raydiry == 0) ? 1
					: ft_abs(1 / rting->raydiry));
}

void	next_step(t_rting *rting)
{
	rting->incrx = rting->raydirx < 0 ? -1 : 1;
	rting->incry = rting->raydiry < 0 ? -1 : 1;
	rting->sidex = rting->raydirx < 0 ? (rting->posx - rting->mapx)
					* rting->distx : (rting->mapx + 1.0 - rting->posx)
					* rting->distx;
	rting->sidey = rting->raydiry < 0 ? (rting->posy - rting->mapy)
					* rting->disty : (rting->mapy + 1.0 - rting->posy)
					* rting->disty;
}

void	straight_square(t_rting *rting, t_map *map)
{
	while (rting->hit == 0)
	{
		if (rting->sidex < rting->sidey)
		{
			rting->sidex += rting->distx;
			rting->mapy += rting->incrx;
			rting->what_side = 0;
		}
		else
		{
			rting->sidey += rting->disty;
			rting->mapy += rting->incry;
			rting->what_side = 1;
		}
		if (map->recup.tab_map[rting->mapx][rting->mapy] > 0)
			rting->hit = 1;
	}
}

void	process_raycasting(t_map *map, t_rting *rting)
{
	int x;

	x = 0;
	while (x < map->recup.resolution[AXE_X])
	{
		ray_position_direction(map, rting, x);
		rting->mapx = rting->posx;
		rting->mapy = rting->posy;
		len_ray(rting);
		next_step(rting);
		straight_square(rting, map);
		//dist_cam_wall(
		x++;
	}
}
