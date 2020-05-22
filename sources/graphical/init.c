/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:04:29 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/22 15:01:34 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h> //

/*static int	deal_key(int key, void *param)
{
	ft_printf("TU RENTRES ICI\n"); //
	ft_putnbr(key); //
	return (SUCCESS);
}*/

void	init_graph(t_graph *gr, t_map *map)
{
	gr->win.mlx_ptr = mlx_init();
	gr->win.win_ptr = mlx_new_window(gr->win.mlx_ptr,
							map->recup.resolution[AXE_X],
							map->recup.resolution[AXE_Y], "Cub3d");
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
}

void	process_window(t_graph *gr)
{
	mlx_clear_window(gr->win.mlx_ptr, gr->win.win_ptr);
	mlx_put_image_to_window(gr->win.mlx_ptr, gr->win.win_ptr, gr->win.img_ptr,
								0, 0);
	//mlx_key_hook(gr->win.win_ptr, deal_key, (void *)0);
	mlx_hook(gr->win.win_ptr, KEYPRESS, 1L << 0, keypress, gr);
	mlx_hook(gr->win.win_ptr, KEYRELEASE, 1L << 1, keyrelease, gr);
	//mlx_loop_hook(gr->win.mlx_ptr, moove, gr);
	mlx_loop(gr->win.mlx_ptr);
}

void	init_map(t_map *map, t_graph *gr)
{
	gr->rting.posx = (double)map->recup.posx + (double)0.5;
	gr->rting.posy = (double)map->recup.posy + (double)0.5;
	get_direction_position(map, gr);
	get_plane(gr, map);
	get_textures(map, gr);
}
