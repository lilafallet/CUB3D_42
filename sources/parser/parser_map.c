/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/18 17:18:57 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	recuperation_map(t_vector *line, t_state_machine *machine)
{
	int ret;
	t_vector	*map;
	static size_t count_line = 0;
	char		c;
	size_t		index;

	ret = TRUE;
	map = vct_new();
	machine->info.tab_map = (enum e_map **)malloc(sizeof(enum e_map *) * (1096)); 
	index = 0;
	vct_addstr(map, vct_getstr(line));
	printf("VERIFICATION_MAP -> line->len = %zu\n", vct_getlen(line)); //
	while (index < vct_getlen(line))
	{
		machine->info.tab_map[count_line] = (enum e_map *)malloc
			(sizeof(enum e_map) * vct_getlen(line));
		c = vct_getfirstchar(map);
		if (ft_iswhitespace(c) == TRUE)
			ret = recuperation_eachelem(machine, count_line, index, VOID);
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
				ret = recuperation_eachelem(machine, count_line, index, POSITION);
		}
		if (ret == ERROR)
			break ;
		vct_pop(map);
		index++;
	}
	count_line++;
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
	free(str);
	return (ret);
}

int	is_map(t_vector *vct)
{
	int	ret;
	t_vector	*cpy_vct;
	size_t		clen;

	ret = TRUE;
	clen = 0;
	cpy_vct = vct_new();
	vct_cpy(cpy_vct, vct);
	clen = vct_clen(cpy_vct, '1');
	if (clen != 0)
		ret = verif_before(cpy_vct, clen);
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


