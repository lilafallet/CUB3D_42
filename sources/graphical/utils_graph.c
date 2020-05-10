/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:57:56 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/10 23:07:40 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static void		get_direction_position(t_map *map, t_rting *rting)
{
	if (map->recup.dirpos == NORTH)
	{
		ft_printf("NORTH\n"); //
		rting->diry = -1;
	}
	else if (map->recup.dirpos == SOUTH)
	{
		ft_printf("SOUTH\n"); //
		rting->diry = 1;
	}
	else if (map->recup.dirpos == WEST)
	{
		ft_printf("WEST\n"); //
		rting->dirx = -1;
	}
	else if (map->recup.dirpos == EAST)
	{
		ft_printf("EAST\n"); //
		rting->dirx = 1;
	}
	printf("rting->diry = %lf\n", rting->diry); //
	printf("rting->dirx = %lf\n", rting->dirx); //
}*/

void	process_window(t_graph *graph, t_map *map)
{
	mlx_put_image_to_window(graph->recup.mlx_ptr, graph->recup.win_ptr,
								graph->recup.img_ptr, 0, 0);
	mlx_destroy_image(graph->recup.mlx_ptr, graph->recup.img_ptr);
}

void	init_graph(t_graph *graph, t_map *map)
{
	int	bits;
	int	endian;
	int	size_line;
	
	graph->recup.mlx_ptr = mlx_init();
	graph->recup.win_ptr = mlx_new_window(graph->recup.mlx_ptr,
								map->recup.resolution[AXE_X],
								map->recup.resolution[AXE_Y],
								"Cub3d");
	graph->recup.img_ptr = mlx_new_image(graph->recup.mlx_ptr,
											map->recup.resolution[AXE_X],
											map->recup.resolution[AXE_Y]);
	graph->recup.data = mlx_get_data_addr(graph->recup.img_ptr,
											&graph->recup.bits,
											&graph->recup.size_line,
											&graph->recup.endian);
	graph->recup.endian = endian;
}

t_graph	*graph_holder(t_graph *graph)
{
	static t_graph	*graph_keep;

	if (graph_keep == NULL && graph != NULL)
		graph_keep = graph;
	return (graph_keep);
}
