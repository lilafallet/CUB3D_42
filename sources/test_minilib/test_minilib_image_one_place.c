/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilib_image_one_place.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 12:09:21 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/04 16:59:13 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_color(int size_line, int bits, t_graph *graph)
{
	int	x; /*width = largeur*/
	int	y; /*height = horizontale*/

	x = 0;
	y = 0;
	while (x < graph->utils.img_x) 
	{
		graph->recup.data[y * size_line + x * bits / 8] =
														graph->utils.r_f;
		graph->recup.data[y * size_line + x * bits / 8 + 1] =
														graph->utils.g_f;
		graph->recup.data[y * size_line + x * bits / 8 + 2] =
														graph->utils.b_f;
		x++;
		if (x == graph->utils.img_x && y < graph->utils.img_y)
		{
			x = 0;
			y++;
		}
	}
}

static	void init(t_graph *graph, t_map *map)
{
	graph->recup.mlx_ptr = mlx_init();
	graph->utils.pos_x = 0; /*deplacement de gauche a droite*/
	graph->utils.pos_y = 0; /*deplacement de haut en bas*/
	graph->utils.img_x = 750; /*gauche->droite*/
	graph->utils.img_y = 900; /*haut->bas*/
	graph->recup.img_ptr = mlx_new_image(graph->recup.mlx_ptr,
											map->recup.str_resolution[AXE_X],
											map->recup.str_resolution[AXE_Y]);
	graph->utils.r_f = map->recup.tab_color_f[B];
	graph->utils.g_f = map->recup.tab_color_f[G];
	graph->utils.b_f = map->recup.tab_color_f[R];
}

void	test_minilib_image_one_place(t_map *map)
{
	int		bits;
	int		endian;
	int		size_line;
	t_graph	graph;

	ft_bzero(&graph, sizeof(graph));
	init(&graph, map);
	graph.recup.data = mlx_get_data_addr(graph.recup.img_ptr, &bits,
											&size_line, &endian);
	fill_color(size_line, bits, &graph);
	graph.recup.win_ptr = mlx_new_window(graph.recup.mlx_ptr,
								map->recup.str_resolution[AXE_X],
								map->recup.str_resolution[AXE_Y],
								"NOM A CHANGER");
	mlx_put_image_to_window(graph.recup.mlx_ptr, graph.recup.win_ptr,
								graph.recup.img_ptr, graph.utils.pos_x,
								graph.utils.pos_y); /*position de l'image*/
	while (42)
	{
	}
}
