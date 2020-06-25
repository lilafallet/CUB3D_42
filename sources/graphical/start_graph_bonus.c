/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:17:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/25 22:17:31 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void		process_init_graph(t_graph *gr, t_map *map)
{
	if (gr->win.img_ptr != NULL)
	{
		mlx_destroy_image(gr->win.mlx_ptr, gr->win.img_ptr);
		gr->win.img_ptr = NULL;
	}
	gr->win.img_ptr = mlx_new_image(gr->win.mlx_ptr,
						map->recup.resolution[AXE_X],
						map->recup.resolution[AXE_Y]);
	if (gr->win.img_ptr == NULL)
	{
		printf_errors(ERROR_IMGPTR, NO_LINE, NO_VECTOR);
		exitred(gr, FAILURE);
	}
	gr->win.data = (int *)mlx_get_data_addr(gr->win.img_ptr, &gr->win.bits,
											&gr->win.size_line,
											&gr->win.endian);
	if (gr->win.data == NULL)
	{
		printf_errors(ERROR_WINDATA, NO_LINE, NO_VECTOR);
		exitred(gr, FAILURE);
	}
}

static void	error_graph(t_graph *gr, unsigned long flag)
{
	if (flag == ERROR_MLX_PTR)
	{
		printf_errors(ERROR_MLX_PTR, NO_LINE, NO_VECTOR);
		exitred(gr, FAILURE);
	}
	if (flag == ERROR_WIN_PTR)
	{
		printf_errors(ERROR_WIN_PTR, NO_LINE, NO_VECTOR);
		exitred(gr, FAILURE);
	}
}

static void	process_savemode(t_map *map, t_graph *gr)
{
	init_map(map, gr);
	gr->win.data = (int *)mlx_get_data_addr(gr->win.img_ptr, &gr->win.bits,
					&gr->win.size_line, &gr->win.endian);
	if (gr->win.data == NULL)
	{
		printf_errors(ERROR_WINDATA, NO_LINE, NO_VECTOR);
		exitred(gr, FAILURE);
	}
	start_raycasting(map, gr);
	if (gr->sp.nb_sprite != 0)
		hub_sprite(map, gr);
	minimap(map, gr);
	life(gr, map);
	if (map->utils.save_mode == TRUE)
		savemode(map, gr);
}

static void	resize_screen(t_graph *gr, t_map *map)
{
	int	screenx;
	int	screeny;

	mlx_get_screen_size(gr->win.mlx_ptr, &screenx, &screeny);
	gr->win.max_screen_width = screenx;
	gr->win.max_screen_height = screeny;
	if (map->recup.resolution[AXE_X] < MAX_AXE_X)
	{
		map->recup.resolution[AXE_X] = MAX_AXE_X;
		map->recup.resolution[AXE_Y] = MAX_AXE_Y;
	}
	if (map->recup.resolution[AXE_Y] < MAX_AXE_Y)
	{
		map->recup.resolution[AXE_X] = MAX_AXE_X;
		map->recup.resolution[AXE_Y] = MAX_AXE_Y;
	}
	if (map->recup.resolution[AXE_X] > screenx)
		map->recup.resolution[AXE_X] = screenx;
	if (map->recup.resolution[AXE_Y] > screeny)
		map->recup.resolution[AXE_Y] = screeny;
}

void		start_graph(t_map *map)
{
	t_graph	gr;

	ft_bzero(&gr, sizeof(gr));
	gr.win.mlx_ptr = mlx_init();
	if (gr.win.mlx_ptr == NULL)
		error_graph(&gr, ERROR_MLX_PTR);
	resize_screen(&gr, map);
	if (map->utils.save_mode == TRUE)
		process_savemode(map, &gr);
	gr.win.win_ptr = mlx_new_window(gr.win.mlx_ptr,
						map->recup.resolution[AXE_X],
						map->recup.resolution[AXE_Y], WINDOW_NAME);
	if (gr.win.win_ptr == NULL)
		error_graph(&gr, ERROR_WIN_PTR);
	init_map(map, &gr);
	mlx_hook(gr.win.win_ptr, KEYPRESS, 1L << 0, keypress, &gr);
	mlx_hook(gr.win.win_ptr, KEYRELEASE, 1L << 1, keyrelease, &gr);
	mlx_hook(gr.win.win_ptr, EXIT, 0, exitred, &gr);
	mlx_loop_hook(gr.win.mlx_ptr, moove, &gr);
	mlx_loop(gr.win.mlx_ptr);
}
