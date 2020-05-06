/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib_losange.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:05:51 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/06 17:43:03 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h> //

static void	fill_pixels(t_graph *graph, int size_line, int bits, int x, int y)
{
	ft_printf("x = %d\n", x); //
	ft_printf("y = %d\n\n", y); //
	graph->recup.data[y * size_line + x * bits / 8] =
													graph->utils.r_f;
	graph->recup.data[y * size_line + x * bits / 8 + 1] =
													graph->utils.g_f;
	graph->recup.data[y * size_line + x * bits / 8 + 2] =
													graph->utils.b_f;
}

static void	init_graph(t_graph *graph, t_map *map)
{
	int	bits;
	int	endian;
	int	size_line;
	
	graph->recup.img_ptr = mlx_new_image(graph->recup.mlx_ptr,
											map->recup.str_resolution[AXE_X],
											map->recup.str_resolution[AXE_Y]);
	graph->utils.r_f = map->recup.tab_color_f[B];
	graph->utils.g_f = map->recup.tab_color_f[G];
	graph->utils.b_f = map->recup.tab_color_f[R];
	graph->recup.data = mlx_get_data_addr(graph->recup.img_ptr, &bits,
											&size_line, &endian);
	graph->recup.bits = bits;
	graph->recup.size_line = size_line;
	graph->recup.endian = endian;

}

static void init_utils(t_graph *graph, t_map *map)
{
	graph->recup.mlx_ptr = mlx_init();
	graph->utils.xstart = map->recup.str_resolution[AXE_X] - 1;
	graph->utils.xend = 0;
	graph->utils.ystart = 0;
	graph->utils.yend = map->recup.str_resolution[AXE_Y] - 1;
	graph->utils.adjust_x = ft_abs(graph->utils.xend - graph->utils.xstart);
	graph->utils.adjust_y = ft_abs(graph->utils.yend - graph->utils.ystart);
	graph->utils.degx = 2 * graph->utils.adjust_x;
	graph->utils.degy = 2 * graph->utils.adjust_y;
	graph->utils.size_x = graph->utils.adjust_x;
	graph->utils.size_y = graph->utils.adjust_y;
}

void	down(t_graph *graph, int xincr, int yincr)
{
	int	i;

	i = 0;
	ft_printf("FIRST CASE\n"); //
	while (i <= graph->utils.size_x) /*tant que plus petit longueur x*/
	{
		fill_pixels(graph, graph->recup.size_line, graph->recup.bits,
						graph->utils.xstart, graph->utils.ystart);
		graph->utils.xstart += xincr;
		graph->utils.adjust_x -= graph->utils.degy;
		if (graph->utils.adjust_x < 0) /*si pixels dessous*/
		{
			graph->utils.ystart += yincr;
			graph->utils.adjust_x += graph->utils.degx;
		}
		i++;	
	}
}

void	up(t_graph *graph, int xincr, int yincr)
{
	int	i;

	i = 0;
	ft_printf("SECOND CASE\n"); //
	while (i <= graph->utils.size_y)
	{
		fill_pixels(graph, graph->recup.size_line, graph->recup.bits,
						graph->utils.xstart, graph->utils.ystart);
		graph->utils.ystart += yincr;
		graph->utils.adjust_y -= graph->utils.degx;
		if (graph->utils.adjust_y < 0) /*si pixel dessus*/
		{
			graph->utils.xstart += xincr;
			graph->utils.adjust_y += graph->utils.degy;
		}
		i++;
	}
}

void	process_window(t_graph *graph, t_map *map)
{
	graph->recup.win_ptr = mlx_new_window(graph->recup.mlx_ptr,
								map->recup.str_resolution[AXE_X],
								map->recup.str_resolution[AXE_Y],
								"NOM A CHANGER");
	mlx_put_image_to_window(graph->recup.mlx_ptr, graph->recup.win_ptr,
								graph->recup.img_ptr, graph->utils.pos_x,
								graph->utils.pos_y);
	mlx_loop(graph->recup.mlx_ptr);

}

void	test_minilib_losange(t_map *map)
{
	int xincr;
	int	yincr;
	t_graph	graph;

	xincr = 1;
	yincr = 1;
	ft_bzero(&graph, sizeof(graph));
	init_utils(&graph, map);
	init_graph(&graph, map);
	if (graph.utils.xstart >= graph.utils.xend) /*dans le cas ou la courbe descend*/
		xincr = -1;
	if (graph.utils.ystart >= graph.utils.yend) /*dans le cas ou la courbe descend*/
		yincr = -1;
	if (graph.utils.size_x > graph.utils.size_y)
		down(&graph, xincr, yincr);
	else
		up(&graph, xincr, yincr);
	process_window(&graph, map);
}
