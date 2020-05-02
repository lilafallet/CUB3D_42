/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:59:20 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/02 18:57:55 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	is_valid(enum e_map map_case)
{
	return ((map_case == OUT || map_case == WALL)
			&& map_case != WRONG_INFO_MAP);
}

static int	is_bad_neighborhood(t_map *map, size_t x, size_t y)
{
	return ((x > 0 && is_valid(map->recup.tab_map[y][x - 1]) == FALSE)
			|| (x + 1 < map->utils.max_index
				&& is_valid(map->recup.tab_map[y][x + 1]) == FALSE)
			|| (y > 0 && is_valid(map->recup.tab_map[y - 1][x]) == FALSE)
			|| (y + 1 < map->utils.max_line
				&& is_valid(map->recup.tab_map[y + 1][x]) == FALSE));
}

int			iter_map(t_map *map, int (*f)(t_map *map, size_t y, size_t x,
						t_state_machine *machine), t_state_machine *machine)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->utils.max_line)
	{
		x = 0;
		while (x < map->utils.max_index)
		{
			if (f(map, y, x, machine) == FALSE)
				return (FALSE);
			x++;
		}
		y++;
	}
	return (TRUE);
}

int			verif_map(t_map *map, size_t y, size_t x, t_state_machine *machine)
{
	if ((map->recup.tab_map[y][x] == OUT)
		&& is_bad_neighborhood(map, x, y) == TRUE)
	{
		machine->info |= ERROR_MAP_NOT_VALID;
		return (FALSE);
	}
	return (TRUE);
}

int			verification_global_map(t_map *map)
{
	t_state_machine *machine;

	machine = get_state_machine(NULL);
	realloc_tab(map, map->utils.max_line, map->utils.max_index,
					map->utils.max_index);
	if (map->utils.count_position != 1)
	{
		machine->info |= ERROR_MAP_NOT_VALID;
		return (ERROR);
	}
	iter_map(map, clean_and_print, machine);
	if (iter_map(map, verif_map, machine) == FALSE)
		return (ERROR);
	return (TRUE);
}
