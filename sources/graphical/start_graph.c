/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/10 02:41:42 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	keys(unsigned char key, int x, int y, t_rting *rting)
{
	if (key == 'a')
	{
		rting->pangle -= 0.1
		if (rting->pangle < 0)
			rting->pangle += 2 * PI;
		rting->deltapx = cos(rting->pangle) * 5;
		rting->deltapy = sin(rting->pangle) * 5;
	}
	else if (key == 'd')
	{
		rting->pangle += 0.1;
		if (rting->pangle > 2 * PI)
			rting->pangle -= 2 * PI;
		rting->delatpx = cos(rting->pangle) * 5;
		rting->deltapy = sin(rting->pangle) * 5;
	}
	else if (key == 'w')
	{
		rting->px += rting->deltapx;
		rting->py += rting->deltapy;
	}
	else if (key == 's')
	{
		rting->px -= rting->deltapx;
		rting->py -= rting->deltapy;
	}
	else if (key == 's')
	//glutPostReDisplay();	
}

static void	process_raycaster(t_rting *rting, t_map *map)
{
	rting->px = (double)map->recup.posx; //player position
	rting->py = (double)map->recup.posy; //player position
	//keys();
	rting->mapx = (double)map->utils.max_index - 1;
	rting->mapy = (double)map->utils.max_line;
	rting->mapsize = rting->mapx * rting->mapy;
}

void	start_graph(t_map *map)
{
	t_graph	graph;
	t_rting rting;
	//6:16 dans la video
	ft_bzero(&rting, sizeof(rting));
	ft_bzero(&graph, sizeof(graph));
	graph_holder(&graph);
	init_graph(&graph, map);
	process_window(&graph, map);
	process_raycaster(&rting, map);	
	mlx_loop(graph.recup.mlx_ptr);
}
