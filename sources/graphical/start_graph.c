/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/12 16:31:12 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	rting->cameraX = 2 * x / (double)640 - 1; //si 1 = droite / 0 = centre / -1 = gauche
	printf("\ncameraX = %lf\n", rting->cameraX); //
	rting->raydirX = rting->dirX + rting->planeX * rting->cameraX;
	printf("raydirX = %lf\n", rting->raydirX); //
	rting->raydirY = rting->dirY + rting->planeY * rting->cameraX;
	printf("raydirY = %lf\n", rting->raydirY); //
	rting->mapX = (int)rting->posX;
	printf("mapX = %d\n", rting->mapX); //
	rting->mapY = (int)rting->posY;
	printf("mapY = %d\n", rting->mapY); //
	rting->deltaDistX = fabs(1 / rting->raydirX);
	printf("deltaDistX = %lf\n", rting->deltaDistX); //
	rting->deltaDistY = fabs(1 / rting->raydirY);
	printf("deltaDistY = %lf\n", rting->deltaDistY); //
}

void	init_step_distray(t_map *map, t_graph *graph, t_rting *rting)
{
	if (rting->raydirX < 0)
	{	
		ft_printf("A GAUCHE\n"); //
		rting->stepX = -1; //on se decale a gauche
		ft_printf("stepX = %d\n", rting->stepX); //
		rting->sideDistX = (rting->posX - rting->mapX) * rting->deltaDistX;
		/*si la direction du rayon est negative (gauche), sideDistX (distance du rayon entre sa
		  position et le cote x du carre) sera le premier cote a gauche*/
		printf("sideDistX = %lf\n", rting->sideDistX); //
	}
	else
	{
		ft_printf("A DROITE\n"); //
		rting->stepX = 1; //on se decale a droite
		ft_printf("stepX = %d\n", rting->stepX); //
		rting->sideDistX = (rting->mapX + 1.0 - rting->posX) * rting->deltaDistX;
		/*si la direction du rayon est positive (droite), sideDistX (distance du rayon entre sa
		  position et le cote x du carre) sera le premier cote a droite*/
		printf("sideDistX = %lf\n", rting->sideDistX); //
	}
	if (rting->raydirY < 0)
	{
		ft_printf("EN HAUT\n"); //
		rting->stepY = -1; //on se decale en haut
		ft_printf("stepY = %d\n", rting->stepY); //
		rting->sideDistY = (rting->posY - rting->mapY) * rting->deltaDistY;
		/*si la direction du rayon est negative (monte), sideDistY (distance du rayon entre sa
		  position et le cote y du carre) sera le premier cote en haut*/
		printf("sideDistY = %lf\n", rting->sideDistY); //
	}
	else
	{
		ft_printf("EN BAS\n"); //
		rting->stepY = 1; //on se decale en bas
		ft_printf("stepY = %d\n", rting->stepY); //
		rting->sideDistY = (rting->mapY + 1.0 - rting->posY) * rting->deltaDistY;
		/*si la direction du rayon est positive (descend), sideDistY (distance du rayon entre sa
		  position et le cote y du carre) sera le premier cote en bas*/
		printf("sideDistY = %lf\n", rting->sideDistY); //
	}
}

void	check_wall(t_map *map, t_graph *graph, t_rting *rting)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rting->sideDistX < rting->sideDistY)
		{
			ft_printf("DISTX > DISTY\n"); //
			rting->sideDistX += rting->deltaDistX;
			printf("sideDistX = %lf\n", rting->sideDistX); //
			rting->mapX += rting->stepX;
			ft_printf("mapX = %d\n", rting->mapX); //
			rting->side = 0;
			ft_printf("side = %d\n", rting->side); //
		}
		else
		{
			ft_printf("DISTY >= DISTX\n"); //
			rting->sideDistY += rting->deltaDistY;
			printf("sideDistY = %lf\n", rting->sideDistY); //
			rting->mapY += rting->stepY;
			ft_printf("mapY = %d\n", rting->mapY); //
			rting->side = 1;
			ft_printf("side = %d\n", rting->side); //
		}
		if (map->recup.tab_map[rting->mapX][rting->mapY] > 0)
		{
			ft_printf("ON A TOUCHE UN MUR\n"); //
			ft_printf("tab_map[%d][%d] = %d\n", rting->mapX, rting->mapY,
						map->recup.tab_map[rting->mapX][rting->mapY]); //
			hit = 1;
		}
	} 
}

void	init_distperpwall(t_map *map, t_graph *graph, t_rting *rting)
{
	if (rting->side == 0)
	{
		rting->perpWallDist = (double)(rting->mapX - rting->posX
								+ (1 - rting->stepX) / 2) / rting->raydirX;
		/*si un cote X est atteind, perpWallDist = nombre de carres que le rayon a traverse dans la
		direction de X*/
		printf("perpWallDist SIDE == 0 = %lf\n", rting->perpWallDist); //
	}
	else
	{
		rting->perpWallDist = (double)(rting->mapY + rting->posY
								+ (1 - rting->stepY) / 2) / rting->raydirY;
		/*si un cote Y est atteind, perpWallDist = nombre de carres que le rayon a traverse dans la
		direction de Y*/
		printf("perpWallDist SIDE != 0 = %lf\n", rting->perpWallDist); //
	}
}

void	calcul_draw(t_map *map, t_graph *graph, t_rting *rting)
{
	rting->lineHeight = (int)(480 / rting->perpWallDist);
	ft_printf("lineHeight = %d\n", rting->lineHeight); //
	rting->drawStart = -rting->lineHeight / 2 + 480 / 2;
	ft_printf("drawStart = %d\n", rting->drawStart); //
	if (rting->drawStart < 0)
	{
		rting->drawStart = 0;
		ft_printf("drawStart SUP 0 = %d\n", rting->drawStart); //
	}
	rting->drawEnd = rting->lineHeight / 2 + 480 / 2;
	ft_printf("drawEnd = %d\n", rting->drawEnd); //
	if (rting->drawEnd >= 480)
	{
		rting->drawEnd = 480 - 1;
		ft_printf("drawEnd SUPERIEUR HAUTEUR= %d\n", rting->drawEnd); //
	}
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
	if (rting->side == 0 && rting->raydirX < 0)
	{
		rting->color_wall = rting->color_south;	
		ft_printf("COLOR SOUTH = BLUE\n");
	}
	if (rting->side == 1 && rting->raydirY > 0)
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
		graph->recup.data[y * 640 + x] = rting->color_wall;
		y++;	
	}
}

void	draw_floor(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;

	y = 480 - 1;
	while (y >= rting->drawEnd)
	{
		graph->recup.data[y * 640 + x] = 0x663300; //MARRON
		y--;
	}
}

void	draw_sky(t_map *map, t_graph *graph, t_rting *rting, int x)
{
	int	y;
	
	y = 0;
	while (y < rting->drawStart)
	{
		graph->recup.data[y * 640 + x] = 0x33CCCC; //BLEU CIEL
		y++;
	}
}

void	start_raycasting(t_map *map, t_graph *graph, t_rting *rting)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 640)
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
	rting->posX = 22;
	rting->posY = 12;
	rting->dirX = -1;
	rting->dirY = 0;
	rting->planeX = 0;
	rting->planeY = 0.66;
	rting->time = 0;
	rting->oldtime = 0;
}

void	start_graph(t_map *map)
{
	t_graph	graph;
	t_rting rting;

	ft_bzero(&rting, sizeof(rting));
	ft_bzero(&graph, sizeof(graph));
	init_map(map, &rting);
	init_graph(&graph, map);
	start_raycasting(map, &graph, &rting);
	graph.recup.win_ptr = mlx_new_window(graph.recup.mlx_ptr, 640, 480, "Cub3d");
	mlx_put_image_to_window(graph.recup.mlx_ptr, graph.recup.win_ptr, graph.recup.img_ptr, 0, 0);
	mlx_loop(graph.recup.mlx_ptr);
}

