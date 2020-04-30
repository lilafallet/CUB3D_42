/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:59:20 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:55:32 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	is_valid(enum e_map map_case)
{
	return ((map_case == OUT || map_case == WALL)
			&& map_case != WRONG_INFO_MAP);
}

static int	is_bad_neighborhood(t_state_machine *map, size_t x, size_t y)
{
	return ((x > 0 && is_valid(map->info.tab_map[y][x - 1]) == FALSE)
			|| (x + 1 < map->info.max_index
				&& is_valid(map->info.tab_map[y][x + 1]) == FALSE)
			|| (y > 0 && is_valid(map->info.tab_map[y - 1][x]) == FALSE)
			|| (y + 1 < map->info.max_line
				&& is_valid(map->info.tab_map[y + 1][x]) == FALSE));
}

int			iter_map(t_state_machine *map,
						int (*f)(t_state_machine *map, size_t y, size_t x))
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->info.max_line)
	{
		x = 0;
		while (x < map->info.max_index)
		{
			if (f(map, y, x) == FALSE)
				return (FALSE);
			x++;
		}
		y++;
	}
	return (TRUE);
}

int			verif_map(t_state_machine *map, size_t y, size_t x)
{
	if ((map->info.tab_map[y][x] == OUT)
		&& is_bad_neighborhood(map, x, y) == TRUE)
	{
		map->information |= ERROR_MAP_NOT_VALID;
		return (FALSE);
	}
	return (TRUE);
}

int			verification_global_map(t_state_machine *map)
{
	realloc_tab(map, map->info.max_line, map->info.max_index,
					map->info.max_index);
	if (map->info.count_position != 1)
	{
		map->information |= ERROR_MAP_NOT_VALID;
		return (ERROR);
	}
	iter_map(map, clean_and_print);
	if (iter_map(map, verif_map) == FALSE)
		return (ERROR);
	return (TRUE);
}
