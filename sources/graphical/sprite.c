/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:30:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/04 15:54:40 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hub_sprite(t_map *map, t_graph *gr)
{
	size_t	x;
	size_t	y;
	double	**tmp_tabcoord;

	y = 0;
	while (y < map->utils.count_line)
	{
		x = 0;
		while (map->recup.tab_map[y][x] != OUT)
		{
			if (map->recup.tab_map[y][x] == SPRITE)
			{
			}
			x++;
		}
		y++;
	}
}
