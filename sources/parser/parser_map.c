/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/17 22:05:27 by lfallet          ###   ########.fr       */
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
	machine->info.tab_map = (enum e_map **)malloc(sizeof(enum e_map *) * (1096)); 
	index = 0;
	//machine->info.tab_map[0][1] = WALL; 
	while ((map = vct_split(line, "12NSEW", ALL_SEP)) != NULL)
	{
		machine->info.tab_map[count_line] = (enum e_map *)malloc(sizeof(enum e_map) * vct_getlen(line));
		ft_printf("VERIFICATION_MAP -> map->str = %s\n", vct_getstr(map)); //
		if (vct_apply(map, IS_WHITESPACE) == TRUE)
		{
			ret = recuperation_void(map, machine, count_line, index);
		}
		if (vct_apply(map, IS_DIGIT) == TRUE)
		{
			c = vct_getfirstchar(map);
			if (c == '0')
				ret = recuperation_void(map, machine, count_line, index);
			if (c == '1')
				ret = recuperation_wall(map, machine, count_line, index);
			if (c == '2')
				ret = recuperation_sprite(map, machine, count_line, index);
		}
		if (vct_apply(map, IS_ALPHA) == TRUE)
		{
			c = vct_getfirstchar(map);
			if (c == 'N' || c == 'S' || c == "W" || c == 'E')
				ret = recuperation_position(map, machine, count_line, index);
		}
		index += vct_getlen(map);
		vct_del(&map);
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
	char	tab_other_map_c[4] = {"S", "R", "F", "C"};
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


