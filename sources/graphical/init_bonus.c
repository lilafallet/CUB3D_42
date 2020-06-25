/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:16:18 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:16:19 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_direction_position(t_map *map, t_graph *gr)
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
	process_init_graph(gr, map);
	if (gr->lf.count <= NOT_DEAD)
	{
		start_raycasting(map, gr);
		if (gr->sp.nb_sprite != 0)
			hub_sprite(map, gr);
		minimap(map, gr);
	}
	if (gr->lf.count <= DEAD)
		life(gr, map);
}

void	process_window(t_graph *gr)
{
	t_map	*map;

	map = get_map(NULL);
	if (map->utils.save_mode == FALSE)
		mlx_put_image_to_window(gr->win.mlx_ptr, gr->win.win_ptr,
									gr->win.img_ptr, 0, 0);
	if (gr->lf.count == REALY_DEAD)
	{
		screen_dead(gr, map, RED);
		mlx_string_put(gr->win.mlx_ptr, gr->win.win_ptr,
						map->recup.resolution[AXE_X] / 2 - 200,
						map->recup.resolution[AXE_Y] / 2, WHITE, YOU_DIED);
		mlx_string_put(gr->win.mlx_ptr, gr->win.win_ptr,
		map->recup.resolution[AXE_X] / 2 - 200,
		map->recup.resolution[AXE_Y] / 2 + 20, WHITE,
		"PLEASE SELECT THE ESCAPE KEY OR THE RED CROSS TO EXIT THE GAME !");
		mlx_string_put(gr->win.mlx_ptr, gr->win.win_ptr,
		map->recup.resolution[AXE_X] / 2 - 200,
		map->recup.resolution[AXE_Y] / 2 + 40, BLACK,
		"IF YOU WANT TO RESTART THE GAME, PLEASE SELECT THE 'R' KEY !");
	}
}

void	init_map(t_map *map, t_graph *gr)
{
	gr->mv.speed_mv = 0.1;
	gr->mv.speed_lk = 0.05;
	gr->sp.raybuff = (double *)malloc(sizeof(double)
				* (map->recup.resolution[AXE_X]
				* map->recup.resolution[AXE_Y]));
	if (gr->sp.raybuff == NULL)
	{
		printf_errors(ERROR_MALLOC_RAYBUFF, NO_LINE, NO_VECTOR);
		exitred(gr, FAILURE);
	}
	gr->rting.posx = (double)map->recup.posx + (double)0.5;
	gr->rting.posy = (double)map->recup.posy + (double)0.5;
	gr->mv.new_posx = gr->rting.posx;
	gr->mv.new_posy = gr->rting.posy;
	gr->mv.old_posx = gr->mv.new_posx;
	gr->mv.old_posy = gr->mv.new_posy;
	get_direction_position(map, gr);
	get_plane(gr, map);
	if ((gr->mv.log & RESTART) == FALSE)
		get_textures(map, gr);
	init_graph(gr, map);
	gr->mv.log &= ~RESTART;
	process_window(gr);
}
