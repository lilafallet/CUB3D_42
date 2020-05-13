/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:04:29 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/13 18:03:19 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_graph(t_graph *graph, t_map *map)
{
	graph->recup.mlx_ptr = mlx_init();
	graph->recup.win_ptr = mlx_new_window(graph->recup.mlx_ptr,
							map->recup.resolution[AXE_X],
							map->recup.resolution[AXE_Y], "Cub3d");
	graph->recup.img_ptr = mlx_new_image(graph->recup.mlx_ptr,
							map->recup.resolution[AXE_X],
							map->recup.resolution[AXE_Y]);
	graph->recup.data = (int *)mlx_get_data_addr(graph->recup.img_ptr,
											&graph->recup.bits,
											&graph->recup.size_line,
											&graph->recup.endian);
}

void	process_window(t_graph *graph)
{
	mlx_put_image_to_window(graph->recup.mlx_ptr, graph->recup.win_ptr,
								graph->recup.img_ptr, 0, 0);
	mlx_destroy_image(graph->recup.mlx_ptr, graph->recup.img_ptr);
	mlx_loop(graph->recup.mlx_ptr);
}

void	init_map(t_map *map, t_rting *rting, t_graph *graph)
{
	rting->posx = (double)map->recup.posx + (double)0.5;
	rting->posy = (double)map->recup.posy + (double)0.5;
	get_direction_position(map, rting);
	get_plane(rting, map);
	get_textures(map, graph, rting);
}
