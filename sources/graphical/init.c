/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:04:29 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/22 18:52:02 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h> //

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
	start_raycasting(map, gr);
}

void	process_window(t_graph *gr)
{
	mlx_clear_window(gr->win.mlx_ptr, gr->win.win_ptr);
	mlx_put_image_to_window(gr->win.mlx_ptr, gr->win.win_ptr, gr->win.img_ptr,
								0, 0);
}

void	init_map(t_map *map, t_graph *gr)
{
	gr->rting.posx = (double)map->recup.posx + (double)0.5;
	gr->rting.posy = (double)map->recup.posy + (double)0.5;
	get_direction_position(map, gr);
	get_plane(gr, map);
	get_textures(map, gr);
}
