/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:22:54 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/13 11:17:22 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycasting(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	ft_printf("INIT RAYCASTING\n"); //
	rting->cameraX = 2 * x / (double)map->recup.resolution[AXE_X] - 1;
	//si 1 = droite / 0 = centre / -1 = gauche
	rting->raydirX = rting->dirX + rting->planeX * rting->cameraX;
	rting->raydirY = rting->dirY + rting->planeY * rting->cameraX;
	rting->mapX = (int)rting->posX;
	rting->mapY = (int)rting->posY;
	rting->deltaDistX = fabs(1 / rting->raydirX);
	rting->deltaDistY = fabs(1 / rting->raydirY);
}

static void	init_step_distray(t_map *map, t_graph *graph, t_rting *rting)
{
	ft_printf("INIT STEP DISTRAY\n"); //
	if (rting->raydirX < 0)
	{	
		rting->stepX = -1; //on se decale a gauche
		rting->sideDistX = (rting->posX - rting->mapX) * rting->deltaDistX;
		/*si la direction du rayon est negative (gauche),
		sideDistX (distance du rayon entre sa position et le cote x du carre)
		sera le premier cote a gauche*/
	}
	else
	{
		rting->stepX = 1; //on se decale a droite
		rting->sideDistX = (rting->mapX + 1.0 - rting->posX) * rting->deltaDistX;
		/*si la direction du rayon est positive (droite),
		sideDistX (distance du rayon entre sa position et le cote x du carre)
		sera le premier cote a droite*/
	}
	if (rting->raydirY < 0)
	{
		rting->stepY = -1; //on se decale en haut
		rting->sideDistY = (rting->posY - rting->mapY) * rting->deltaDistY;
		/*si la direction du rayon est negative (monte),
		sideDistY (distance du rayon entre sa position et le cote y du carre)
		sera le premier cote en haut*/
	}
	else
	{
		rting->stepY = 1; //on se decale en bas
		rting->sideDistY = (rting->mapY + 1.0 - rting->posY) * rting->deltaDistY;
		/*si la direction du rayon est positive (descend),
		sideDistY (distance du rayon entre sa position et le cote y du carre)
		sera le premier cote en bas*/
	}
}

static void	check_wall(t_map *map, t_graph *graph, t_rting *rting)
{
	rting->hit = 0;
	ft_printf("CHECK WALL\n"); //
	while (rting->hit == 0)
	{
		if (rting->sideDistX < rting->sideDistY)
		{
			rting->sideDistX += rting->deltaDistX;
			rting->mapX += rting->stepX;
			rting->side = 0;
		}
		else
		{
			rting->sideDistY += rting->deltaDistY;
			rting->mapY += rting->stepY;
			rting->side = 1;
		}
		if (map->recup.tab_map[rting->mapY][rting->mapX] == 1)
			rting->hit = 1;
	} 
}

static void	calcul_draw(t_map *map, t_graph *graph, t_rting *rting)
{
	ft_printf("CALCUL DRAW\n"); //
	if (rting->side == 0)
	{
		rting->perpWallDist = (rting->mapX - rting->posX
								+ (1 - rting->stepX) / 2) / rting->raydirX;
		/*si un cote X est atteind, perpWallDist = nombre de carres que
		le rayon a traverse dans la direction de X*/
	}
	else
	{
		rting->perpWallDist = (rting->mapY - rting->posY
								+ (1 - rting->stepY) / 2) / rting->raydirY;
		/*si un cote Y est atteind, perpWallDist = nombre de carres que
		le rayon a traverse dans la direction de Y*/
	}
	rting->lineHeight = (int)(map->recup.resolution[AXE_Y]
							/ rting->perpWallDist);
	rting->drawStart = -rting->lineHeight / 2 + map->recup.resolution[AXE_Y]
							/ 2;
	if (rting->drawStart < 0)
		rting->drawStart = 0;
	rting->drawEnd = rting->lineHeight / 2 + map->recup.resolution[AXE_Y] / 2;
	if (rting->drawEnd >= map->recup.resolution[AXE_Y])
		rting->drawEnd = map->recup.resolution[AXE_Y] - 1;
}

void	start_raycasting(t_map *map, t_graph *graph, t_rting *rting)
{
	int	x;

	x = 0;
	ft_printf("\nSTART RAYCASTING\n"); //
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
