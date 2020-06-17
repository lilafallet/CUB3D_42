/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:04:29 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/17 17:29:28 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h> //

void		get_direction_position(t_map *map, t_graph *gr)
{
	if (map->recup.dirpos == NORTH)
		gr->rting.diry = -1;
	else if (map->recup.dirpos == SOUTH)
		gr->rting.diry = 1;
	else if (map->recup.dirpos == WEST)
		gr->rting.dirx = -1;
	else if (map->recup.dirpos == EAST)
		gr->rting.dirx = 1;
}

void	get_plane(t_graph *gr, t_map *map)
{
	if (map->recup.dirpos == NORTH)
		gr->rting.planecamx = 0.66;
	else if (map->recup.dirpos == SOUTH)
		gr->rting.planecamx = -0.66;
	else if (map->recup.dirpos == WEST)
		gr->rting.planecamy = -0.66;
	else if (map->recup.dirpos == EAST)
		gr->rting.planecamy = 0.66;
}

void	init_graph(t_graph *gr, t_map *map)
{

	if (gr->win.img_ptr != NULL)
	{
		mlx_destroy_image(gr->win.mlx_ptr, gr->win.img_ptr);
		gr->win.img_ptr = NULL;
	}
	gr->win.img_ptr = mlx_new_image(gr->win.mlx_ptr,
						map->recup.resolution[AXE_X],
						map->recup.resolution[AXE_Y]);
	gr->win.data = (int *)mlx_get_data_addr(gr->win.img_ptr, &gr->win.bits,
											&gr->win.size_line,
											&gr->win.endian);
	if (gr->lf.count != 14)
	{
		start_raycasting(map, gr);
		if (gr->sp.nb_sprite != 0)
			hub_sprite(map, gr);
		life(gr, map); //BONUS
	}
	if (gr->lf.count == 14)
	{
		died(gr, map);
	}
}

void	process_window(t_graph *gr)
{
	t_map	*map;

	map = get_map(NULL);
	mlx_put_image_to_window(gr->win.mlx_ptr, gr->win.win_ptr, gr->win.img_ptr,
									0, 0);
	if (gr->lf.count == 14)
	{
		mlx_string_put(gr->win.mlx_ptr, gr->win.win_ptr,
						map->recup.resolution[AXE_X] / 2 - 200,
						map->recup.resolution[AXE_Y] / 2, 0xFFFFFF,
						"YOU DIED");
		mlx_string_put(gr->win.mlx_ptr, gr->win.win_ptr,
						map->recup.resolution[AXE_X] / 2 - 200,
						map->recup.resolution[AXE_Y] / 2 + 20, 0xFFFFFF,
						"PLEASE SELECT THE ESCAPE KEY OR THE RED CROSS TO EXIT THE GAME");
	}
}

void	init_map(t_map *map, t_graph *gr)
{
	gr->sp.raybuff = malloc(sizeof(double) * (map->recup.resolution[AXE_X]
						* map->recup.resolution[AXE_Y]));
	//PROTEGER
	gr->rting.posx = (double)map->recup.posx + (double)0.5;
	gr->rting.posy = (double)map->recup.posy + (double)0.5;
	gr->mv.new_posx = gr->rting.posx;
	gr->mv.new_posy = gr->rting.posy;
	gr->mv.old_posx = gr->mv.new_posx;
	gr->mv.old_posy = gr->mv.new_posy;
	get_direction_position(map, gr);
	get_plane(gr, map);
	get_textures(map, gr);
}
