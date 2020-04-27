/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recuperation_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:40:05 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/27 11:43:43 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				clean_and_print(t_state_machine *machine, size_t i, size_t j)
{
	if (machine->info.tab_map[i][j] == STOP)
		machine->info.tab_map[i][j] = OUT;
	return (TRUE);
}

static int		fill_tab(ssize_t index_char, t_state_machine *machine,
		size_t index)
{
	int	ret;

	ret = TRUE;
	if (index_char < WAY_WALL_SPRITE)
		machine->info.tab_map[machine->info.count_line][index] =
			(enum e_map)index_char;
	else if (index_char > OUTMAP)
		machine->info.tab_map[machine->info.count_line][index] = OUT;
	else if (machine->info.count_position == 0)
	{
		machine->info.tab_map[machine->info.count_line][index] = POSITION;
		machine->info.count_position++;
	}
	else
		ret = ERROR;
	return (ret);
}

static int		process_recuperation_map(t_state_machine *machine, size_t index,
		t_vector *map)
{
	char			c;
	ssize_t			index_char;
	t_vector		*vct_char;
	int				ret;

	ret = TRUE;
	c = vct_getfirstchar(map);
	vct_char = vct_new();
	vct_addstr(vct_char, STR_MAP);
	index_char = vct_chr(vct_char, c);
	if (index_char == FAILURE)
		ret = ERROR;
	vct_del(&vct_char);
	if (ret != ERROR)
		ret = fill_tab(index_char, machine, index);
	vct_pop(map);
	vct_del(&vct_char);
	return (ret);
}

int				recuperation_map(t_vector *line, t_state_machine *machine)
{
	int				ret;
	t_vector		*map;
	size_t			index;

	ret = TRUE;
	index = 0;
	map = vct_dup(line);
	realloc_tab(machine, machine->info.count_line + 1, machine->info.max_index,
			vct_getlen(line) + 1);
	while (index < vct_getlen(line) && ret != ERROR)
	{
		ret = process_recuperation_map(machine, index, map);
		if (ret == ERROR)
			break ;
		index++;
	}
	if (ret != ERROR)
		machine->info.tab_map[machine->info.count_line][index] = STOP;
	if (index > machine->info.max_index)
		machine->info.max_index = index;
	machine->info.count_line++;
	machine->info.max_line = machine->info.count_line;
	vct_del(&map);
	return (ret);
}
