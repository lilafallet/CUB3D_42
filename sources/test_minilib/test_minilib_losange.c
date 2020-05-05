/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib_losange.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:05:51 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/05 18:04:32 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h> //

static void	fill_pixels(t_graph *graph, int size_line, int bits, int x, int y)
{
	graph->recup.data[y * size_line + x * bits / 8] =
													graph->utils.r_f;
	graph->recup.data[y * size_line + x * bits / 8 + 1] =
													graph->utils.g_f;
	graph->recup.data[y * size_line + x * bits / 8 + 2] =
													graph->utils.b_f;
}

static	void init(t_graph *graph, t_map *map)
{
	graph->recup.mlx_ptr = mlx_init();
	graph->utils.pos_x = 0; //deplacement de gauche a droite
	graph->utils.pos_y = 0; //deplacement de haut en bas
	graph->utils.img_x = 1900; //gauchgraph->recup.droite
	graph->utils.img_y = 1080; //haut->bas
	graph->recup.img_ptr = mlx_new_image(graph->recup.mlx_ptr,
											map->recup.str_resolution[AXE_X],
											map->recup.str_resolution[AXE_Y]);
	graph->utils.r_f = map->recup.tab_color_f[B];
	graph->utils.g_f = map->recup.tab_color_f[G];
	graph->utils.b_f = map->recup.tab_color_f[R];
}

void	test_minilib_losange(t_map *map)
{
	int	x1 = 0;
	int	x2 = map->recup.str_resolution[AXE_X];
	int	y1 = map->recup.str_resolution[AXE_Y] - 1;
	int	y2 = 0;
	int	ex = abs(x2 - x1);
	int	ey = abs(y2 - y1);
	int	dx = 2 * ex;
	int	dy = 2 * ey;
	int	Dx = ex;
	int	Dy = ey;
	int	i = 0;
	int Xincr = 1;
	int	Yincr = 1;
	int	bits;
	int	endian;
	int	size_line;
	t_graph	graph;

	ft_bzero(&graph, sizeof(graph));
	init(&graph, map);
	graph.recup.data = mlx_get_data_addr(graph.recup.img_ptr, &bits,
											&size_line, &endian);
	if (x1 >= x2)
		Xincr = -1;
	if (y1 >= y2)
		Yincr = -1;
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			fill_pixels(&graph, size_line, bits, x1, y1);
			i++;
			x1 += Xincr;
			ex -= dy;
			if (ex < 0)
			{
				y1 += Yincr;
				ex += dx;
			}	
		}
	}
	if (Dx < Dy)
	{
		while (i <= Dy)
		{
			fill_pixels(&graph, size_line, bits, x1, y1);
			i++;
			y1 += Yincr;
			ey -= dx;
			if (ey < 0)
			{
				x1 += Xincr;
				ey += dy;
			}
		}
	}
	graph.recup.win_ptr = mlx_new_window(graph.recup.mlx_ptr,
								map->recup.str_resolution[AXE_X],
								map->recup.str_resolution[AXE_Y],
								"NOM A CHANGER");
	mlx_put_image_to_window(graph.recup.mlx_ptr, graph.recup.win_ptr,
								graph.recup.img_ptr, graph.utils.pos_x,
								graph.utils.pos_y); //position de l'image
	while (42)
	{
	}
}
