/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:22:54 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/14 15:35:46 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycasting(t_map *map, t_graph *gr, int x)
{
	gr->rting.camerax = 2 * x / (double)map->recup.resolution[AXE_X] - 1;
	//si 1 = droite / 0 = centre / -1 = gauche
	gr->rting.raydirx = gr->rting.dirx + gr->rting.planecamx
							* gr->rting.camerax;
	gr->rting.raydiry = gr->rting.diry + gr->rting.planecamy
							* gr->rting.camerax;
	gr->rting.mapx = (int)gr->rting.posx;
	gr->rting.mapy = (int)gr->rting.posy;
	gr->rting.deltadistx = fabs(1 / gr->rting.raydirx);
	gr->rting.deltadisty = fabs(1 / gr->rting.raydiry);
}

static void	init_step_distray(t_map *map, t_graph *gr)
{
	if (gr->rting.raydirx < 0)
	{	
		gr->rting.stepx = -1; //on se decale a gauche
		gr->rting.distx = (gr->rting.posx - gr->rting.mapx)
							* gr->rting.deltadistx;
		/*si la direction du rayon est negative (gauche),
		  distx (distance du rayon entre sa position et le cote x du carre)
		  sera le premier cote a gauche*/
	}
	else
	{
		gr->rting.stepx = 1; //on se decale a droite
		gr->rting.distx = (gr->rting.mapx + 1.0 - gr->rting.posx)
							* gr->rting.deltadistx;
		/*si la direction du rayon est positive (droite),
		  distx (distance du rayon entre sa position et le cote x du carre)
		  sera le premier cote a droite*/
	}
	if (gr->rting.raydiry < 0)
	{
		gr->rting.stepy = -1; //on se decale en haut
		gr->rting.disty = (gr->rting.posy - gr->rting.mapy)
							* gr->rting.deltadisty;
		/*si la direction du rayon est negative (monte),
		  disty (distance du rayon entre sa position et le cote y du carre)
		  sera le premier cote en haut*/
	}
	else
	{
		gr->rting.stepy = 1; //on se decale en bas
		gr->rting.disty = (gr->rting.mapy + 1.0 - gr->rting.posy)
							* gr->rting.deltadisty;
		/*si la direction du rayon est positive (descend),
		  disty (distance du rayon entre sa position et le cote y du carre)
		  sera le premier cote en bas*/
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
			gr->rting.side = 0;
		}
		else
		{
			gr->rting.disty += gr->rting.deltadisty;
			gr->rting.mapy += gr->rting.stepy;
			gr->rting.side = 1;
		}
		if (map->recup.tab_map[gr->rting.mapy][gr->rting.mapx] == 1)
			gr->rting.hit = 1;
	} 
}

static void	calcul_draw(t_map *map, t_graph *gr)
{
	gr->draw.height_line = (int)(map->recup.resolution[AXE_Y]
			/ gr->rting.perpwalldist);
	gr->draw.start_draw = -gr->draw.height_line / 2
							+ map->recup.resolution[AXE_Y] / 2;
	if (gr->draw.start_draw < 0)
		gr->draw.start_draw = 0;
	gr->draw.end_draw = gr->draw.height_line / 2
							+ map->recup.resolution[AXE_Y] / 2;
	if (gr->draw.end_draw >= map->recup.resolution[AXE_Y])
		gr->draw.end_draw = map->recup.resolution[AXE_Y] - 1;
}

void	start_raycasting(t_map *map, t_graph *gr)
{
	int	x;

	x = 0;
	while (x < map->recup.resolution[AXE_X])
	{
		init_raycasting(map, gr, x);
		init_step_distray(map, gr);
		check_wall(map, gr);
		if (gr->rting.side == 0)
		{
			gr->rting.perpwalldist = (gr->rting.mapx - gr->rting.posx
					+ (1 - gr->rting.stepx) / 2) / gr->rting.raydirx;
			/*si un cote X est atteind, perpwalldist = nombre de carres que
			  le rayon a traverse dans la direction de X*/
		}
		else
		{
			gr->rting.perpwalldist = (gr->rting.mapy - gr->rting.posy
					+ (1 - gr->rting.stepy) / 2) / gr->rting.raydiry;
			/*si un cote Y est atteind, perpwalldist = nombre de carres que
			  le rayon a traverse dans la direction de Y*/
		}
		shadow_wall(map, gr);
		calcul_draw(map, gr);
		hub_draw(map, gr, x);
		x++;
	}
}
