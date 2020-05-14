/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:52:06 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/14 16:05:02 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_graph	*gr_holder(t_graph *gr)
{
	static t_graph	*gr_keep;

	if (gr_keep == NULL && gr != NULL)
		gr_keep = gr;
	return (gr_keep);
}

int	get_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void		get_direction_position(t_map *map, t_graph *gr)
{
	if (map->recup.dirpos == NORTH)
		gr->rting.diry = -1;
	else if (map->recup.dirpos == SOUTH)
		gr->rting.diry = 1;
	else if (map->recup.dirpos == WEST)
		gr->rting.dirx = -1;
	else if (map->recup.dirpos == EAST)
		gr->rting.dirx = 1;
}

void	get_plane(t_graph *gr, t_map *map)
{
	if (map->recup.dirpos == NORTH)
		gr->rting.planecamx = 0.66;
	else if (map->recup.dirpos == SOUTH)
		gr->rting.planecamx = -0.66;
	else if (map->recup.dirpos == WEST)
		gr->rting.planecamy = -0.66;
	else if (map->recup.dirpos == EAST)
		gr->rting.planecamy = 0.66;
}
