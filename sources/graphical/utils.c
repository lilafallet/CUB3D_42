/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 10:52:06 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/14 15:21:45 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_gr	*gr_holder(t_gr *gr)
{
	static t_gr	*gr_keep;

	if (gr_keep == NULL && gr != NULL)
		gr_keep = gr;
	return (gr_keep);
}

int	get_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void		get_direction_position(t_map *map, t_gr *gr)
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

void	get_plane(t_gr *gr, t_map *map)
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
