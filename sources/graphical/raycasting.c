/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:22:54 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/13 16:15:24 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycasting(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	rting->camerax = 2 * x / (double)map->recup.resolution[AXE_X] - 1;
	//si 1 = droite / 0 = centre / -1 = gauche
	rting->raydirx = rting->dirx + rting->planecamx * rting->camerax;
	rting->raydiry = rting->diry + rting->planecamy * rting->camerax;
	rting->mapx = (int)rting->posx;
	rting->mapy = (int)rting->posy;
	rting->deltadistx = fabs(1 / rting->raydirx);
	rting->deltadisty = fabs(1 / rting->raydiry);
}

static void	init_step_distray(t_map *map, t_graph *graph, t_rting *rting)
{
	if (rting->raydirx < 0)
	{	
		rting->stepx = -1; //on se decale a gauche
		rting->distx = (rting->posx - rting->mapx) * rting->deltadistx;
		/*si la direction du rayon est negative (gauche),
		distx (distance du rayon entre sa position et le cote x du carre)
		sera le premier cote a gauche*/
	}
	else
	{
		rting->stepx = 1; //on se decale a droite
		rting->distx = (rting->mapx + 1.0 - rting->posx) * rting->deltadistx;
		/*si la direction du rayon est positive (droite),
		distx (distance du rayon entre sa position et le cote x du carre)
		sera le premier cote a droite*/
	}
	if (rting->raydiry < 0)
	{
		rting->stepy = -1; //on se decale en haut
		rting->disty = (rting->posy - rting->mapy) * rting->deltadisty;
		/*si la direction du rayon est negative (monte),
		disty (distance du rayon entre sa position et le cote y du carre)
		sera le premier cote en haut*/
	}
	else
	{
		rting->stepy = 1; //on se decale en bas
		rting->disty = (rting->mapy + 1.0 - rting->posy) * rting->deltadisty;
		/*si la direction du rayon est positive (descend),
		disty (distance du rayon entre sa position et le cote y du carre)
		sera le premier cote en bas*/
	}
}

static void	check_wall(t_map *map, t_graph *graph, t_rting *rting)
{
	rting->hit = 0;
	while (rting->hit == 0)
	{
		if (rting->distx < rting->disty)
		{
			rting->distx += rting->deltadistx;
			rting->mapx += rting->stepx;
			rting->side = 0;
		}
		else
		{
			rting->disty += rting->deltadisty;
			rting->mapy += rting->stepy;
			rting->side = 1;
		}
		if (map->recup.tab_map[rting->mapy][rting->mapx] == 1)
			rting->hit = 1;
	} 
}

static void	calcul_draw(t_map *map, t_graph *graph, t_rting *rting)
{
	if (rting->side == 0)
	{
		rting->perpwalldist = (rting->mapx - rting->posx
								+ (1 - rting->stepx) / 2) / rting->raydirx;
		/*si un cote X est atteind, perpwalldist = nombre de carres que
		le rayon a traverse dans la direction de X*/
	}
	else
	{
		rting->perpwalldist = (rting->mapy - rting->posy
								+ (1 - rting->stepy) / 2) / rting->raydiry;
		/*si un cote Y est atteind, perpwalldist = nombre de carres que
		le rayon a traverse dans la direction de Y*/
	}
	rting->height_line = (int)(map->recup.resolution[AXE_Y]
							/ rting->perpwalldist);
	rting->start_draw = -rting->height_line / 2 + map->recup.resolution[AXE_Y]
							/ 2;
	if (rting->start_draw < 0)
		rting->start_draw = 0;
	rting->end_draw = rting->height_line / 2 + map->recup.resolution[AXE_Y] / 2;
	if (rting->end_draw >= map->recup.resolution[AXE_Y])
		rting->end_draw = map->recup.resolution[AXE_Y] - 1;
}

void	start_raycasting(t_map *map, t_graph *graph, t_rting *rting)
{
	int	x;

	x = 0;
	while (x < map->recup.resolution[AXE_X])
	{
		init_raycasting(map, graph, rting, x);
		init_step_distray(map, graph, rting);
		check_wall(map, graph, rting);
		calcul_draw(map, graph, rting);
		hub_draw(map, graph, rting, x);
		x++;
	}
}
