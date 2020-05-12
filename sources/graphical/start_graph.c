/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/12 19:46:08 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	rting->cameraX = 2 * x / (double)map->recup.resolution[AXE_X] - 1; //si 1 = droite / 0 = centre / -1 = gauche
	rting->raydirX = rting->dirX + rting->planeX * rting->cameraX;
	rting->raydirY = rting->dirY + rting->planeY * rting->cameraX;
	rting->mapX = (int)rting->posX;
	rting->mapY = (int)rting->posY;
	rting->deltaDistX = fabs(1 / rting->raydirX); //verif 0
	rting->deltaDistY = fabs(1 / rting->raydirY); //verif 0
}

void	init_step_distray(t_map *map, t_graph *graph, t_rting *rting)
{
	if (rting->raydirX < 0)
	{	
		rting->stepX = -1; //on se decale a gauche
		rting->sideDistX = (rting->posX - rting->mapX) * rting->deltaDistX;
		/*si la direction du rayon est negative (gauche), sideDistX (distance du rayon entre sa
		  position et le cote x du carre) sera le premier cote a gauche*/
	}
	else
	{
		rting->stepX = 1; //on se decale a droite
		rting->sideDistX = (rting->mapX + 1.0 - rting->posX) * rting->deltaDistX;
		/*si la direction du rayon est positive (droite), sideDistX (distance du rayon entre sa
		  position et le cote x du carre) sera le premier cote a droite*/
	}
	if (rting->raydirY < 0)
	{
		rting->stepY = -1; //on se decale en haut
		rting->sideDistY = (rting->posY - rting->mapY) * rting->deltaDistY;
		/*si la direction du rayon est negative (monte), sideDistY (distance du rayon entre sa
		  position et le cote y du carre) sera le premier cote en haut*/
	}
	else
	{
		rting->stepY = 1; //on se decale en bas
		rting->sideDistY = (rting->mapY + 1.0 - rting->posY) * rting->deltaDistY;
		/*si la direction du rayon est positive (descend), sideDistY (distance du rayon entre sa
		  position et le cote y du carre) sera le premier cote en bas*/
	}
}

void	check_wall(t_map *map, t_graph *graph, t_rting *rting)
{
	rting->hit = 0;
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
		if (map->recup.tab_map[rting->mapX][rting->mapY] == 1)
			rting->hit = 1;
	} 
}

void	init_distperpwall(t_map *map, t_graph *graph, t_rting *rting)
{
	if (rting->side == 0)
	{
		rting->perpWallDist = (rting->mapX - rting->posX
								+ (1 - rting->stepX) / 2) / rting->raydirX;
		/*si un cote X est atteind, perpWallDist = nombre de carres que le rayon a traverse dans la
		direction de X*/
	}
	else
	{
		rting->perpWallDist = (rting->mapY - rting->posY
								+ (1 - rting->stepY) / 2) / rting->raydirY;
		/*si un cote Y est atteind, perpWallDist = nombre de carres que le rayon a traverse dans la
		direction de Y*/
	}
}

void	calcul_draw(t_map *map, t_graph *graph, t_rting *rting)
{
	rting->lineHeight = (int)(map->recup.resolution[AXE_Y] / rting->perpWallDist);
	rting->drawStart = -rting->lineHeight / 2 + map->recup.resolution[AXE_Y] / 2;
	if (rting->drawStart < 0)
		rting->drawStart = 0;
	rting->drawEnd = rting->lineHeight / 2 + map->recup.resolution[AXE_Y] / 2;
	if (rting->drawEnd >= map->recup.resolution[AXE_Y])
		rting->drawEnd = map->recup.resolution[AXE_Y] - 1;
}

void	color_wall(t_map *map, t_graph *graph, t_rting *rting)
{
	rting->color_south = 0x0066CC; //BLUE
	rting->color_north = 0x990000; //RED
	rting->color_east = 0xFFD700; //YELLOW
	rting->color_west = 0x009900; //GREEN

	if (rting->side == 0 && rting->raydirX > 0)
	{
		rting->color_wall = rting->color_north;	
		ft_printf("COLOR NORTH = RED\n");
	}
	else if (rting->side == 0 && rting->raydirX < 0)
	{
		rting->color_wall = rting->color_south;	
		ft_printf("COLOR SOUTH = BLUE\n");
	}
	else if (rting->side == 1 && rting->raydirY > 0)
	{
		rting->color_wall = rting->color_east;	
		ft_printf("COLOR EAST = YELLOW\n");
	}
	else
	{
		rting->color_wall = rting->color_west;	
		ft_printf("COLOR WEST = GREEN\n");
	}
}

void	draw_wall(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;

	y = rting->drawStart;
	while (y < rting->drawEnd)
	{	
		graph->recup.data[y * map->recup.resolution[AXE_X] + x] = rting->color_wall;
		y++;	
	}
}

void	draw_floor(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;

	y = map->recup.resolution[AXE_Y] - 1;
	while (y >= rting->drawEnd)
	{
		graph->recup.data[y * map->recup.resolution[AXE_X] + x] = 0x663300; //MARRON
		y--;
	}
}

void	draw_sky(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;
	
	y = 0;
	while (y < rting->drawStart)
	{
		graph->recup.data[y * map->recup.resolution[AXE_X] + x] = 0x33CCCC; //BLEU CIEL
		y++;
	}
}

void	start_raycasting(t_map *map, t_graph *graph, t_rting *rting)
{
	int	x;

	x = 0;
	while (x <= map->recup.resolution[AXE_X] - 1)
	{
		init_raycasting(map, graph, rting, x);
		init_step_distray(map, graph, rting);
		check_wall(map, graph, rting);
		init_distperpwall(map, graph, rting);
		calcul_draw(map, graph, rting);
		color_wall(map, graph, rting);
		draw_wall(map, graph, rting, x);
		draw_floor(map, graph, rting, x);
		draw_sky(map, graph, rting, x);
		x++;
	}
}

void	init_map(t_map *map, t_rting *rting)
{
	rting->posX = (double)map->recup.posx;
	rting->posY = (double)map->recup.posy;
	get_direction_position(map, rting);
	get_plane(rting, map);
}

void	start_graph(t_map *map)
{
	t_graph	graph;
	t_rting rting;

	ft_bzero(&rting, sizeof(rting));
	ft_bzero(&graph, sizeof(graph));
	graph.recup.mlx_ptr = mlx_init();
	init_map(map, &rting);
	init_graph(&graph, map);
	start_raycasting(map, &graph, &rting);
	mlx_put_image_to_window(graph.recup.mlx_ptr, graph.recup.win_ptr, graph.recup.img_ptr, 0, 0);
	mlx_loop(graph.recup.mlx_ptr);
}

