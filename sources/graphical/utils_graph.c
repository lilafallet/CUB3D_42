/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:57:56 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/09 20:14:22 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		get_direction_position(t_map *map, t_rting *rting)
{
	if (map->recup.dirpos == NORTH)
	{
		ft_printf("NORTH\n"); //
		rting->diry = -1;
	}
	if (map->recup.dirpos == SOUTH)
	{
		ft_printf("SOUTH\n"); //
		rting->diry = 1;
	}
	if (map->recup.dirpos == WEST)
	{
		ft_printf("WEST\n"); //
		rting->dirx = -1;
	}
	if (map->recup.dirpos == EAST)
	{
		ft_printf("EAST\n"); //
		rting->dirx = 1;
	}
	ft_printf("rting->diry = %d\n", rting->diry); //
	ft_printf("rting->dirx = %d\n", rting->dirx); //
}

void	init_raycasting(t_map *map, t_rting *rting)
{
	rting->posx = (double)map->recup.posx;
	rting->posy = (double)map->recup.posy;
	ft_printf("\nmap->recup.posx = %d\n", map->recup.posx); //
	ft_printf("map->recup.posy = %d\n", map->recup.posy); //
	printf("\nrting->posx = %lf\n", rting->posx); //
	printf("rting->posy = %lf\n", rting->posy); //
	get_direction_position(map, rting);
	rting->planey = 0.66; 
}

void	process_window(t_graph *graph, t_map *map)
{
	mlx_put_image_to_window(graph->recup.mlx_ptr, graph->recup.win_ptr,
								graph->recup.img_ptr, graph->utils.pos_x,
								graph->utils.pos_y);
	mlx_destroy_image(graph->recup.mlx_ptr, graph->recup.img_ptr);
	mlx_loop(graph->recup.mlx_ptr);

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
	//graph->utils.r_f = map->recup.tab_color_f[B];
	//graph->utils.g_f = map->recup.tab_color_f[G];
	//graph->utils.b_f = map->recup.tab_color_f[R];
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
