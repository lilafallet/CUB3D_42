/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 14:39:03 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/02 19:01:41 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static int		deal_key(int key, void *param)
{
	ft_putchar_fd('X', 1);
	(void)key;
	(void)param;
	return (SUCCESS);
}*/

static void	fill_color(t_map *map, int size_line, int bpp,
						t_graph *graph)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->recup.str_resolution[AXE_X])
	{
		graph->recup.data[y * size_line + x * bpp / 8 ] = graph->utils.color1;
		graph->recup.data[y * size_line + x * bpp / 8 + 1] =
															graph->utils.color2;
		graph->recup.data[y * size_line + x * bpp / 8 + 2] =
															graph->utils.color3;
		x++;
		if (x == map->recup.str_resolution[AXE_X] &&
				y < map->recup.str_resolution[AXE_Y])
		{
			x = 0;
			y++;
		}
	}
}

static	void init(t_graph *graph, t_map *map)
{
	graph->recup.mlx_ptr = mlx_init();
	graph->utils.color_total = map->recup.tab_color_f[R]
								+ (map->recup.tab_color_f[G] << 8)
								+ (map->recup.tab_color_f[B] << 16);
	graph->recup.img_ptr = mlx_new_image(graph->recup.mlx_ptr,
										map->recup.str_resolution[AXE_X],
										map->recup.str_resolution[AXE_Y]);
	graph->recup.img_color = mlx_get_color_value(graph->recup.mlx_ptr,
													graph->utils.color_total);
	graph->utils.color1 = map->recup.tab_color_f[B];
	graph->utils.color2 = map->recup.tab_color_f[G];
	graph->utils.color3 = map->recup.tab_color_f[R];

}

void	test_minilib(t_map *map)
{
	int   bpp;
	int   endian;
	int	size_line;
	t_graph	graph;
	//t_map	*map;

	//map = get_map(NULL);
	ft_bzero(&graph, sizeof(graph));
	init(&graph, map);
	graph.recup.data = mlx_get_data_addr(graph.recup.img_ptr, &bpp, &size_line,
										&endian);
	fill_color(map, size_line, bpp, &graph);
	graph.recup.win_ptr = mlx_new_window(graph.recup.mlx_ptr,
								map->recup.str_resolution[AXE_X],
								map->recup.str_resolution[AXE_Y],
								"NOM A CHANGER");
	mlx_put_image_to_window(graph.recup.mlx_ptr, graph.recup.win_ptr,
								graph.recup.img_ptr, 0, 0);
	while (42)
	{
	}
}
