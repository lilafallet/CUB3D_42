/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/18 10:59:14 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_graph(t_map *map)
{
	t_graph	gr;
	int	screenx;
	int	screeny;

	ft_bzero(&gr, sizeof(gr));
	gr.win.mlx_ptr = mlx_init();
	mlx_get_screen_size(gr.win.mlx_ptr, &screenx, &screeny);
	if (map->recup.resolution[AXE_X] > screenx)
		map->recup.resolution[AXE_X] = screenx;
	if (map->recup.resolution[AXE_Y] > screeny)
		map->recup.resolution[AXE_Y] = screeny;
	//ft_printf("screenx = %d\n", screenx); //
	//ft_printf("screeny = %d\n", screeny); //
	if (map->utils.save_mode == TRUE)
	{
		init_map(map, &gr);
		gr.win.img_ptr = mlx_new_image(gr.win.mlx_ptr,
								map->recup.resolution[AXE_X],
								map->recup.resolution[AXE_Y]);
		gr.win.data = (int *)mlx_get_data_addr(gr.win.img_ptr, &gr.win.bits,
												&gr.win.size_line,
												&gr.win.endian);
		start_raycasting(map, &gr);
		if (gr.sp.nb_sprite != 0)
			hub_sprite(map, &gr);
		if (map->utils.save_mode == TRUE)
			savemode(map, &gr);
	}
	gr.win.win_ptr = mlx_new_window(gr.win.mlx_ptr,
						map->recup.resolution[AXE_X],
						map->recup.resolution[AXE_Y], "Cub3D");
	init_map(map, &gr);
	mlx_hook(gr.win.win_ptr, KEYPRESS, 1L << 0, keypress, &gr);
	mlx_hook(gr.win.win_ptr, KEYRELEASE, 1L << 1, keyrelease, &gr);
	mlx_hook(gr.win.win_ptr, EXIT, 0, exitred, &gr);
	mlx_loop_hook(gr.win.mlx_ptr, moove, &gr);
	mlx_loop(gr.win.mlx_ptr);
}
