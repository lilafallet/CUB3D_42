/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recuperation_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:40:05 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/24 17:41:37 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	fill_line(t_state_machine *machine, enum e_map **cpy_tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < machine->info.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) *
						(machine->info.max_index));
		ft_memset(cpy_tab[i], STOP, machine->info.max_index);
		j = 0;
		while (j < machine->info.max_index
				&& machine->info.tab_map[i][j] != STOP)
		{
			cpy_tab[i][j] = machine->info.tab_map[i][j];
			j++;
		}
		while (j < machine->info.max_index)
			cpy_tab[i][j++] = STOP;
		free(machine->info.tab_map[i]);
		i++;
	}
	return (i);
}

int		realloc_tab(t_state_machine *machine, size_t count_line,
						size_t old_index, size_t new_index)
{
	enum e_map **cpy_tab;
	size_t		i;

	if (old_index == 0 || new_index > old_index)
		machine->info.max_index = new_index;
	cpy_tab  = (enum e_map **)malloc(sizeof(enum e_map *) * (count_line)); 
	ft_bzero(cpy_tab, count_line);
	i = fill_line(machine, cpy_tab);
	if (count_line != machine->info.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) * 
						machine->info.max_index);
		ft_memset(cpy_tab[i], STOP, machine->info.max_index);
	}	
	free(machine->info.tab_map);
	machine->info.tab_map = cpy_tab;
	return (SUCCESS);
}

static int	process_recuperation_map(t_state_machine *machine,
										size_t count_line, size_t index,
										t_vector *map)
{
	char	c;
	ssize_t	index_char;
	static	size_t	count_position = 0;
	t_vector			*vct_char;

	c = vct_getfirstchar(map);
	vct_char = vct_new();
	vct_addstr(vct_char, STR_MAP);
	index_char = vct_chr(vct_char, c);	
	if (index_char < WAY_WALL_SPRITE)
			machine->info.tab_map[count_line][index] = (enum e_map)index_char;
	else if (index_char > OUTMAP)
			machine->info.tab_map[count_line][index] = OUT;
	else if (count_position == 0)
	{
		machine->info.tab_map[count_line][index] = POSITION;
		count_position++;
	}
	else
		return (ERROR);
	vct_pop(map);
	vct_del(&vct_char);
	return (TRUE);
}

int	recuperation_map(t_vector *line, t_state_machine *machine)
{
	int 				ret;
	t_vector			*map;
	static size_t 		count_line = 0;
	size_t				index;

	ret = TRUE;
	index = 0;
	map = vct_dup(line);
	realloc_tab(machine, count_line + 1, machine->info.max_index,
					vct_getlen(line) + 1);
	while (index < vct_getlen(line) && ret != ERROR)
	{
		ret = process_recuperation_map(machine, count_line, index, map);
		if (ret == ERROR)
			break ;
		index++;
	}
	if (ret != ERROR)
		machine->info.tab_map[count_line][index] = STOP;
	if (index > machine->info.max_index)
		machine->info.max_index = index;
	count_line++;
	machine->info.max_line = count_line;
	vct_del(&map);
	return (ret);
}
