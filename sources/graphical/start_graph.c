/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/13 00:54:13 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	init_raycasting(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	ft_printf("INIT RAYCASTING\n"); //
	rting->cameraX = 2 * x / (double)map->recup.resolution[AXE_X] - 1; //si 1 = droite / 0 = centre / -1 = gauche
	rting->raydirX = rting->dirX + rting->planeX * rting->cameraX;
	rting->raydirY = rting->dirY + rting->planeY * rting->cameraX;
	rting->mapX = (int)rting->posX;
	rting->mapY = (int)rting->posY;
	rting->deltaDistX = fabs(1 / rting->raydirX);
	rting->deltaDistY = fabs(1 / rting->raydirY);
}

void	init_step_distray(t_map *map, t_graph *graph, t_rting *rting)
{
	ft_printf("INIT STEP DISTRAY\n"); //
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

void	init_distperpwall(t_map *map, t_graph *graph, t_rting *rting)
{
	ft_printf("INIT DISTPERWALL\n"); //
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
	ft_printf("CALCUL DRAW\n"); //
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
	
	ft_printf("COLOR WALL\n"); //
	if (rting->side == 0 && rting->raydirX > 0)
		rting->color_wall = rting->color_north;	
	else if (rting->side == 0 && rting->raydirX < 0)
		rting->color_wall = rting->color_south;	
	else if (rting->side == 1 && rting->raydirY > 0)
		rting->color_wall = rting->color_east;	
	else
		rting->color_wall = rting->color_west;	
}

void	draw_wall(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;

	y = rting->drawStart;
	ft_printf("DRAW WALL\n"); //
	while (y < rting->drawEnd)
	{	
		graph->recup.data[y * map->recup.resolution[AXE_X] + x] = rting->color_wall;
		y++;	
	}
}

void	draw_floor(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;
	int	floor_color;

	y = map->recup.resolution[AXE_Y] - 1;
	floor_color = get_rgb(map->recup.tab_color_f[R], map->recup.tab_color_f[G],
							map->recup.tab_color_f[B]); 
	ft_printf("DRAW FLOOR\n"); //
	while (y >= rting->drawEnd)
	{
		graph->recup.data[y * map->recup.resolution[AXE_X] + x] = floor_color; //MARRON
		y--;
	}
}

void	draw_sky(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;
	int	sky_color;
	
	y = 0;
	ft_printf("DRAW SKY\n"); //
	sky_color = get_rgb(map->recup.tab_color_c[R], map->recup.tab_color_c[G],
							map->recup.tab_color_c[B]); 
	while (y < rting->drawStart)
	{
		graph->recup.data[y * map->recup.resolution[AXE_X] + x] = sky_color; //BLEU CIEL
		y++;
	}
}

void	start_raycasting(t_map *map, t_graph *graph, t_rting *rting)
{
	int	x;

	x = 0;
	ft_printf("START RAYCASTING\n"); //
	while (x < map->recup.resolution[AXE_X])
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
	rting->posX = (double)map->recup.posx + (double)0.5;
	rting->posY = (double)map->recup.posy + (double)0.5;
	printf("posX = %lf\n", rting->posX); //
	printf("posY = %lf\n", rting->posY); //
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

