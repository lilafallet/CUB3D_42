/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib_losange.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:05:51 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/05 21:59:03 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h> //

static void	fill_pixels(t_graph *graph, int size_line, int bits, int x, int y)
{
	ft_printf("x	=	%d\n", x); //
	ft_printf("y	=	%d\n\n", y); //
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
	graph->recup.x1 = 0;
	graph->recup.x2 = map->recup.str_resolution[AXE_X] - 1;
	graph->recup.y1 = map->recup.str_resolution[AXE_Y] - 1;
	graph->recup.y2 = 0;
	graph->recup.ex = abs(graph->recup.x2 - graph->recup.x1); //faire fonction abs
	graph->recup.ey = abs(graph->recup.y2 - graph->recup.y1); //faire fonction abs
	graph->recup.dx = 2 * graph->recup.ex;
	graph->recup.dy = 2 * graph->recup.ey;
	graph->recup.Dx = graph->recup.ex;
	graph->recup.Dy = graph->recup.ey;
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

void	first_case(t_graph *graph, int size_line, int bits, int Xincr, int Yincr)
{
	int	i;

	i = 0;
	while (i <= graph->recup.Dx)
	{
		fill_pixels(graph, size_line, bits, graph->recup.x1, graph->recup.y1);
		graph->recup.x1 += Xincr;
		graph->recup.ex -= graph->recup.dy;
		if (graph->recup.ex < 0)
		{
			graph->recup.y1 += Yincr;
			graph->recup.ex += graph->recup.dx;
		}
		i++;	
	}
}

void	test_minilib_losange(t_map *map)
{
	int	i;
	int Xincr;
	int	Yincr;
	int	bits;
	int	endian;
	int	size_line;
	t_graph	graph;

	i = 0;
	Xincr = 1;
	Yincr = 1;
	ft_bzero(&graph, sizeof(graph));
	init(&graph, map);
	graph.recup.data = mlx_get_data_addr(graph.recup.img_ptr, &bits,
											&size_line, &endian);
	if (graph.recup.x1 >= graph.recup.x2)
		Xincr = -1;
	if (graph.recup.y1 >= graph.recup.y2)
		Yincr = -1;
	if (graph.recup.Dx > graph.recup.Dy)
		first_case(&graph, size_line, bits, Xincr, Yincr);
	if (graph.recup.Dx < graph.recup.Dy)
	{
		while (i <= graph.recup.Dy)
		{
			fill_pixels(&graph, size_line, bits, graph.recup.x1, graph.recup.y1);
			graph.recup.y1 += Yincr;
			graph.recup.ey -= graph.recup.dx;
			if (graph.recup.ey < 0)
			{
				graph.recup.x1 += Xincr;
				graph.recup.ey += graph.recup.dy;
			}
			i++;
		}
	}
	graph.recup.win_ptr = mlx_new_window(graph.recup.mlx_ptr,
								map->recup.str_resolution[AXE_X],
								map->recup.str_resolution[AXE_Y],
								"NOM A CHANGER");
	mlx_put_image_to_window(graph.recup.mlx_ptr, graph.recup.win_ptr,
								graph.recup.img_ptr, graph.utils.pos_x,
								graph.utils.pos_y); //position de l'image
	mlx_loop(graph.recup.mlx_ptr);
}
