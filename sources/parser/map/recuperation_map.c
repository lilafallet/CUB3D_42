/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recuperation_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:40:05 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 23:11:18 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				clean_and_print(t_state_machine *map, size_t i, size_t j)
{
	if (map->info.tab_map[i][j] == STOP)
		map->info.tab_map[i][j] = OUT;
	return (TRUE);
}

static int		fill_tab(ssize_t index_char, t_state_machine *map,
		size_t index)
{
	int	ret;

	ret = TRUE;
	if (index_char < WAY_WALL_SPRITE)
		map->info.tab_map[map->info.count_line][index] =
			(enum e_map)index_char;
	else if (index_char > OUTMAP)
		map->info.tab_map[map->info.count_line][index] = OUT;
	else if (map->info.count_position == 0)
	{
		map->info.tab_map[map->info.count_line][index] = POSITION;
		map->info.count_position++;
	}
	else
		ret = ERROR;
	return (ret);
}

static int		process_recuperation_map(t_state_machine *map, size_t index,
		t_vector *map_inf)
{
	char			c;
	ssize_t			index_char;
	t_vector		*vct_char;
	int				ret;

	ret = TRUE;
	c = vct_getfirstchar(map_inf);
	vct_char = vct_new();
	vct_addstr(vct_char, STR_MAP);
	index_char = vct_chr(vct_char, c);
	if (index_char == FAILURE)
		ret = ERROR;
	vct_del(&vct_char);
	if (ret != ERROR)
		ret = fill_tab(index_char, map, index);
	vct_pop(map_inf);
	vct_del(&vct_char);
	return (ret);
}

int				recuperation_map(t_vector *line, t_state_machine *map)
{
	int				ret;
	t_vector		*map_inf;
	size_t			index;

	ret = TRUE;
	index = 0;
	map_inf = vct_dup(line);
	realloc_tab(map, map->info.count_line + 1, map->info.max_index,
			vct_getlen(line) + 1);
	while (index < vct_getlen(line) && ret != ERROR)
	{
		ret = process_recuperation_map(map, index, map_inf);
		if (ret == ERROR)
			break ;
		index++;
	}
	if (ret != ERROR)
		map->info.tab_map[map->info.count_line][index] = STOP;
	if (index > map->info.max_index)
		map->info.max_index = index;
	map->info.count_line++;
	map->info.max_line = map->info.count_line;
	vct_del(&map_inf);
	return (ret);
}
