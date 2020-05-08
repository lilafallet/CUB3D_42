/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:57:56 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/08 18:42:44 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void		get_direction_position(t_map *map, t_rting *rting)
{
	if (map->recup.dirpos == NORTH)
		rting->diry = -1;
	if (map->recup.dirpos == SOUTH)
		rting->diry = 1;
	if (map->recup.dirpos == WEST)
		rting->dirx = -1;
	if (map->recup.dirpos == EAST)
		rting->dirx = 1;
	ft_printf("rting->diry = %d\n", rting->diry); //
	ft_printf("rting->dirx = %d\n", rting->dirx); //
}

void	init_retracing(t_map *map)
{
	t_rting rting;

	ft_bzero(&rting, sizeof(rting));
	rting.posx = map->recup.posx;
	rting.posy = map->recup.posy;
	get_direction_position(map, &rting);
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

void	init_graph(t_graph *graph, t_map *map)
{
	int	bits;
	int	endian;
	int	size_line;
	
	graph->recup.mlx_ptr = mlx_init();
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

t_graph	*graph_holder(t_graph *graph)
{
	static t_graph	*graph_keep;

	if (graph_keep == NULL && graph != NULL)
		graph_keep = graph;
	return (graph_keep);
}
