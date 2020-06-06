/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:30:50 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/06 12:29:08 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	count_sprite(t_map *map)
{
	size_t	x;
	size_t	y;
	size_t	count;

	y = 0;
	count = 0;
	while (y < map->utils.count_line)
	{
		x = 0;
		while (map->recup.tab_map[y][x] != OUT)
		{
			if (map->recup.tab_map[y][x] == SPRITE)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	init_coord_sprite(t_map *map, t_graph *gr, size_t nb_sprite)
{
	size_t	x;
	size_t	y;
	size_t	count;

	y = 0;
	count = 0;
	gr->sp.pos = (t_position *)malloc(sizeof(t_position) * nb_sprite);
	while (y < map->utils.count_line)
	{
		x = 0;
		while (map->recup.tab_map[y][x] != OUT)
		{
			if (map->recup.tab_map[y][x] == SPRITE)
			{
				gr->sp.pos[count].x = x + 0.5;
				gr->sp.pos[count].y = y + 0.5;
				/*printf("sprite[%zu]{x %lf, y %lf}\n", count,
							gr->sp.pos[count].x, gr->sp.pos[count].y);*/
				count++;
			}
			x++;
		}
		y++;
	}
}

void		hub_sprite(t_map *map, t_graph *gr)
{
	size_t	nb_sprite;
	
	nb_sprite = count_sprite(map);
	init_coord_sprite(map, gr, nb_sprite);
}
