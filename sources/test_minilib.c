/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:39:03 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 23:07:09 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		deal_key(int key, void *param)
{
	ft_putchar_fd('X', 1);
	(void)key;
	(void)param;
	return (SUCCESS);
}

static void	fill_color(t_state_machine *map, int size_line, int bpp,
						t_graph *graph)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->info.str_resolution[AXE_X])
	{
		graph->inf.data[y * size_line + x * bpp / 8 ] = graph->inf.color1;
		graph->inf.data[y * size_line + x * bpp / 8 + 1] = graph->inf.color2;
		graph->inf.data[y * size_line + x * bpp / 8 + 2] = graph->inf.color3;
		x++;
		if (x == map->info.str_resolution[AXE_X] &&
				y < map->info.str_resolution[AXE_Y])
		{
			x = 0;
			y++;
		}
	}
}

static	void init(t_graph *graph, t_state_machine *map)
{
	graph->inf.mlx_ptr = mlx_init();
	graph->inf.color_total = map->info.tab_color_f[R]
								+ (map->info.tab_color_f[G] << 8)
								+ (map->info.tab_color_f[B] << 16);
	graph->inf.img_ptr = mlx_new_image(graph->inf.mlx_ptr,
										map->info.str_resolution[AXE_X],
										map->info.str_resolution[AXE_Y]);
	graph->inf.img_color = mlx_get_color_value(graph->inf.mlx_ptr,
													graph->inf.color_total);
	graph->inf.color1 = map->info.tab_color_f[B];
	graph->inf.color2 = map->info.tab_color_f[G];
	graph->inf.color3 = map->info.tab_color_f[R];

}

void	test_minilib(t_state_machine *map)
{
	int   bpp;
	int   endian;
	int	size_line;
	t_graph	graph;

	ft_bzero(&graph, sizeof(graph));
	init(&graph, map);
	graph.inf.data = mlx_get_data_addr(graph.inf.img_ptr, &bpp, &size_line,
										&endian);
	fill_color(map, size_line, bpp, &graph);
	graph.inf.win_ptr = mlx_new_window(graph.inf.mlx_ptr,
								map->info.str_resolution[AXE_X],
								map->info.str_resolution[AXE_Y],
								"NOM A CHANGER");
	mlx_put_image_to_window(graph.inf.mlx_ptr, graph.inf.win_ptr,
								graph.inf.img_ptr, 0, 0);
	while (42)
	{
	}
}
