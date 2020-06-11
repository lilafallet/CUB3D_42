/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/11 15:04:52 by lfallet          ###   ########.fr       */
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
	//ft_printf("screenx = %d\n", screenx); //
	//ft_printf("screeny = %d\n", screeny); //
	if (map->recup.resolution[AXE_X] > screenx)
		map->recup.resolution[AXE_X] = screenx;
	if (map->recup.resolution[AXE_Y] > screeny)
		map->recup.resolution[AXE_Y] = screeny;
	gr.win.win_ptr = mlx_new_window(gr.win.mlx_ptr,
							map->recup.resolution[AXE_X],
							map->recup.resolution[AXE_Y], "Cub3d");
	init_map(map, &gr);
	init_graph(&gr, map);
	process_window(&gr);
	mlx_hook(gr.win.win_ptr, KEYPRESS, 1L << 0, keypress, &gr);
	mlx_hook(gr.win.win_ptr, KEYRELEASE, 1L << 1, keyrelease, &gr);
	mlx_hook(gr.win.win_ptr, EXIT, 0, exitred, &gr);
	mlx_loop_hook(gr.win.mlx_ptr, moove, &gr);
	mlx_loop(gr.win.mlx_ptr);
}
