/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:22:54 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/14 10:00:42 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycasting(t_map *map, t_graph *gr, int x)
{
	gr->rting.camerax = 2 * x / (double)map->recup.resolution[AXE_X] - 1;
	//si 1 = droite / 0 = centre / -1 = gauche
	//correspond que l'on voit, se deplace de gauche a droite en fonction de x*/
	gr->rting.raydirx = gr->rting.dirx + gr->rting.planecamx
							* gr->rting.camerax;
	gr->rting.raydiry = gr->rting.diry + gr->rting.planecamy
							* gr->rting.camerax;
	gr->rting.mapx = (int)gr->rting.posx;
	gr->rting.mapy = (int)gr->rting.posy;
	gr->rting.deltadistx = fabs(1 / gr->rting.raydirx);
	gr->rting.deltadisty = fabs(1 / gr->rting.raydiry);
	/*distance que le rayon doit parcourir du cote x/y au suivant*/
}

static void	init_step_distray(t_graph *gr)
{
	if (gr->rting.raydirx < 0) //si le rayon est a gauche
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
	while (gr->rting.hit == 0) //tant qu'on a pas tappe de mur
	{
		if (gr->rting.distx < gr->rting.disty)
		{
			gr->rting.distx += gr->rting.deltadistx; /*on ajoute la distance du
			rayon a la distance du prochain rayon*/
			gr->rting.mapx += gr->rting.stepx; /*on ajoute au carre actuel ou
			se trouve le rayon sur x et on y ajoute step (si on se deplace a
			gauche ou a droite)*/
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
			/ gr->rting.perpwalldist); /*la hauteur du mur == resolution sur y
	divise par la distance du rayon*/
	gr->draw.start = -gr->draw.height_line / 2
							+ map->recup.resolution[AXE_Y] / 2;
	/*le debut des pixels == la negative de la hauteur du mur / 2 + la
	resolution sur Y / 2*/
	if (gr->draw.start < 0)
		gr->draw.start = 0;
	gr->draw.end = gr->draw.height_line / 2
							+ map->recup.resolution[AXE_Y] / 2;
	//le fin des pixels == la hauteur du mur / 2 + la resolution sur Y / 2
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
		//shadow_wall(gr);
		calcul_draw(map, gr);
		gr->sp.raybuff[x] = gr->rting.perpwalldist;
		draw_wall(map, gr, x);
		hub_draw(map, gr, x);
		x++;
	}
}
