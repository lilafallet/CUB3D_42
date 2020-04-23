/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/23 18:39:55 by lfallet          ###   ########.fr       */
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
	vct_addstr(vct_char, "012NSWE \t");
	index_char = vct_chr(vct_char, c);	
	if (index_char < 3)
			machine->info.tab_map[count_line][index] = (enum e_map)index_char;
	else if (index_char > 6)
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

static int	verif_before(t_vector *vct, size_t clen)
{
	char	*str;
	size_t	i;
	int		ret;

	str = vct_getstr(vct);
	i = 0;
	ret = TRUE;
	while (i < clen)
	{
		if (str[i] != SPACE && str[i] != TAB)
			ret = ERROR;
		i++;
	}
	return (ret);
}

int	is_map(t_vector *vct)
{
	int	ret;
	t_vector	*cpy_vct;
	size_t		clen;

	ret = TRUE;
	clen = 0;
	cpy_vct = vct_dup(vct);
	clen = vct_clen(cpy_vct, '1');
	if (clen != 0)
		ret = verif_before(cpy_vct, clen);
	vct_del(&cpy_vct);
	return (ret);
}

static size_t	fill_tab_str(size_t tab_len[4], t_vector *vct,
								char *tab_other_map_str[4])
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		tab_len[i] = vct_strlen(vct, tab_other_map_str[i]);
		i++;
	}
	return (i);
}

static void	fill_tab_c(size_t tab_len[9], size_t i, char tab_other_map_c[4],
						t_vector *vct)
{
	size_t	index;

	index = 0;
	while (i < 8)
	{
		tab_len[i] = vct_clen(vct, tab_other_map_c[index]);
		i++;
		index++;
	}
}

int	what_information_map(t_vector *vct, size_t clen_map,
							t_state_machine *machine)
{
	char	*tab_other_map_str[4] = {"NO", "SO", "WE", "EA"};
	char	tab_other_map_c[4] = {'S', 'R', 'F', 'C'};
	size_t	tab_len[9];
	size_t	index;
	size_t	i;

	index = 0;
	i = fill_tab_str(tab_len, vct, tab_other_map_str);
	fill_tab_c(tab_len, i, tab_other_map_c, vct);
	tab_len[8] = clen_map;
	index = ft_bubblesort_minindex(tab_len, 9);
	if (tab_len[0] == clen_map && tab_len[1] == clen_map
			&& tab_len[2] == clen_map && tab_len[3] == clen_map 
			&& tab_len[4] == clen_map && tab_len[5] == clen_map
			&& tab_len[6] == clen_map && tab_len[7] == clen_map)
		return (TRUE);
	if (index == 0 || index == 1 || index == 2 || index == 3 || index == 4)
		machine->state = TEXTURE;
	if (index == 5)
		machine->state = RESOLUTION;
	if (index == 6 || index == 7)
		machine->state = COLOR;
	return (NEXT);
}
