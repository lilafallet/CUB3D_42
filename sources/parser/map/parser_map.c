/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:55:09 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t			fill_line(t_state_machine *map, enum e_map **cpy_tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < map->info.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) *
				(map->info.max_index));
		ft_memset(cpy_tab[i], STOP, map->info.max_index);
		j = 0;
		while (j < map->info.max_index
				&& map->info.tab_map[i][j] != STOP)
		{
			cpy_tab[i][j] = map->info.tab_map[i][j];
			j++;
		}
		while (j < map->info.max_index)
			cpy_tab[i][j++] = STOP;
		free(map->info.tab_map[i]);
		i++;
	}
	return (i);
}

int				realloc_tab(t_state_machine *map, size_t count_line,
		size_t old_index, size_t new_index)
{
	enum e_map	**cpy_tab;
	size_t		i;

	if (old_index == 0 || new_index > old_index)
		map->info.max_index = new_index;
	cpy_tab = (enum e_map **)malloc(sizeof(enum e_map *) * (count_line));
	ft_bzero(cpy_tab, map->info.count_line);
	i = fill_line(map, cpy_tab);
	if (count_line != map->info.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) *
				map->info.max_index);
		ft_memset(cpy_tab[i], STOP, map->info.max_index);
	}
	free(map->info.tab_map);
	map->info.tab_map = cpy_tab;
	return (SUCCESS);
}

static int		verif_before(t_vector *vct, size_t clen)
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

int				is_map(t_vector *vct)
{
	int			ret;
	t_vector	*cpy_vct;
	size_t		clen;

	ret = TRUE;
	clen = 0;
	cpy_vct = vct_dup(vct);
	clen = vct_clen(cpy_vct, CHAR_WALL);
	if (clen != 0)
		ret = verif_before(cpy_vct, clen);
	vct_del(&cpy_vct);
	return (ret);
}
