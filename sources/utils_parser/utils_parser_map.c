/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:59:20 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/25 09:44:37 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	is_valid(enum e_map map_case)
{
	return (map_case == OUT || map_case == WALL);
}

static int	is_bad_neighborhood(t_state_machine *machine, size_t x, size_t y)
{
	return ((x > 0 && is_valid(machine->info.tab_map[y][x - 1]) == FALSE)
			|| (x + 1 < machine->info.max_index
				&& is_valid(machine->info.tab_map[y][x + 1]) == FALSE)
			|| (y > 0 && is_valid(machine->info.tab_map[y - 1][x]) == FALSE)
			|| (y + 1 < machine->info.max_line
				&& is_valid(machine->info.tab_map[y + 1][x]) == FALSE));
}

int			iter_map(t_state_machine *machine,
						int (*f)(t_state_machine *machine, size_t y, size_t x))
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < machine->info.max_line)
	{
		x = 0;
		while (x < machine->info.max_index)
		{
			if (f(machine, y, x) == FALSE)
				return (FALSE);
			x++;
		}
		y++;
	}
	return (TRUE);
}

int			verif_map(t_state_machine *machine, size_t y, size_t x)
{
	if ((machine->info.tab_map[y][x] == OUT)
		&& is_bad_neighborhood(machine, x, y) == TRUE)
	{
		machine->information |= ERROR_MAP;
		return (FALSE);
	}
	return (TRUE);
}

int			verification_global_map(t_state_machine *machine)
{
	realloc_tab(machine, machine->info.max_line, machine->info.max_index,
					machine->info.max_index);
	iter_map(machine, clean_and_print);
	if (iter_map(machine, verif_map) == FALSE)
		return (ERROR);
	return (TRUE);
}
