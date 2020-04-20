/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/20 16:16:12 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //

int		realloc_tab(t_state_machine *machine, size_t count_line, size_t old_index, size_t new_index)
{
	enum e_map **cpy_tab;
	size_t		i;
	size_t		j;

	if (old_index == 0 || new_index > old_index)
		machine->info.max_index = new_index;
	cpy_tab  = (enum e_map **)malloc(sizeof(enum e_map *) * (count_line)); 
	ft_bzero(cpy_tab, count_line);
	i = 0;
	while (i < machine->info.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) * (machine->info.max_index));
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
	ft_printf("count_line %d, max_line %d\n", count_line, machine->info.max_line);
	if (count_line != machine->info.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) * machine->info.max_index);
		ft_memset(cpy_tab[i], STOP, machine->info.max_index);
	}	
	free(machine->info.tab_map);
	machine->info.tab_map = cpy_tab;
	return (SUCCESS);
}

int	recuperation_map(t_vector *line, t_state_machine *machine)
{
	int ret;
	t_vector	*map;
	static size_t count_line = 0;
	char		c;
	size_t		index;
	ssize_t		index_char;
	static size_t		count_position = 0;
	t_vector	*vct_char;

	ret = TRUE;
	index = 0;
	map = vct_dup(line);
	vct_char = vct_new();
	vct_addstr(vct_char, "012NSWE \t");
	realloc_tab(machine, count_line + 1, machine->info.max_index, vct_getlen(line) + 1);
	printf("VERIFICATION_MAP -> line->len = %zu\n", vct_getlen(line)); //
	while (index < vct_getlen(line) && ret != ERROR)
	{
		c = vct_getfirstchar(map);
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
			ret = ERROR;
/*
		if (ft_iswhitespace(c) == TRUE)
			ret = recuperation_eachelem(machine, count_line, index, OUT);
		if (ft_isdigit(c) == TRUE)
		{
			if (c == '0')
				ret = recuperation_eachelem(machine, count_line, index, VOID);
			if (c == '1')
				ret = recuperation_eachelem(machine, count_line, index, WALL);
			if (c == '2')
				ret = recuperation_eachelem(machine, count_line, index, SPRITE);
		}
		if (ft_isalpha(c) == TRUE)
		{	
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				ret = recuperation_eachelem(machine, count_line, index, POSITION);
				count_position++;
				printf("COUNT_POSITION ===================================%zu\n", count_position); //
			}
		}
		if (count_position >= 2)
	}	
		{
			ft_printf("RENTRE ICI JE T'EN SUPPLI PLEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAASE\n"); //
			ret = ERROR;
		}	
		if (ret == ERROR)
			break ;*/
		vct_pop(map);
		index++;
	}
	if (ret != ERROR)
		machine->info.tab_map[count_line][index] = STOP;
	if (index > machine->info.max_index)
		machine->info.max_index = index;
//	ret = verif_line(line, machine, count_line);
	count_line++;
	machine->info.max_line = count_line;
	vct_del(&map);
	vct_del(&vct_char);
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

int	what_information_map(t_vector *vct, size_t clen_map, t_state_machine *machine)
{
	char	*tab_other_map_str[4] = {"NO", "SO", "WE", "EA"};
	char	tab_other_map_c[4] = {'S', 'R', 'F', 'C'};
	size_t	tab_len[9];
	size_t	i;
	size_t	index;

	i = 0;	
	while (i < 4)
	{
		tab_len[i] = vct_strlen(vct, tab_other_map_str[i]);
		i++;
	}
	index = 0;
	while (i < 8)
	{
		tab_len[i] = vct_clen(vct, tab_other_map_c[index]);
		i++;
		index++;
	}
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


