/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:52:06 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/13 11:03:06 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_graph	*graph_holder(t_graph *graph)
{
	static t_graph	*graph_keep;

	if (graph_keep == NULL && graph != NULL)
		graph_keep = graph;
	return (graph_keep);
}

int	get_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void		get_direction_position(t_map *map, t_rting *rting)
{
	if (map->recup.dirpos == NORTH)
	{
		printf("NORTH\n"); //
		rting->dirY = -1;
	}
	else if (map->recup.dirpos == SOUTH)
	{
		printf("SOUTH\n"); //
		rting->dirY = 1;
	}
	else if (map->recup.dirpos == WEST)
	{
		printf("WEST\n"); //
		rting->dirX = -1;
	}
	else if (map->recup.dirpos == EAST)
	{
		printf("EAST\n"); //
		rting->dirX = 1;
	}
}

void	get_plane(t_rting *rting, t_map *map)
{
	if (map->recup.dirpos == NORTH)
		rting->planeX = 0.66;
	else if (map->recup.dirpos == SOUTH)
		rting->planeX = -0.66;
	else if (map->recup.dirpos == WEST)
		rting->planeY = -0.66;
	else if (map->recup.dirpos == EAST)
		rting->planeY = 0.66;
}