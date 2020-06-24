/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:46:34 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 13:47:08 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t			fill_line(t_map *map, enum e_map **cpy_tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->utils.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) *
				(map->utils.max_index));
		if (cpy_tab[i] == NULL)
			error(map, ERROR_MALLOC_CPYTAB, NO_VECTOR);
		ft_memset(cpy_tab[i], STOP, map->utils.max_index);
		j = 0;
		while (j < map->utils.max_index
				&& map->recup.tab_map[i][j] != STOP)
		{
			cpy_tab[i][j] = map->recup.tab_map[i][j];
			j++;
		}
		while (j < map->utils.max_index)
			cpy_tab[i][j++] = STOP;
		free(map->recup.tab_map[i]);
		i++;
	}
	return (i);
}

int				realloc_tab(t_map *map, size_t count_line,
		size_t old_index, size_t new_index)
{
	enum e_map	**cpy_tab;
	size_t		i;

	if (old_index == 0 || new_index > old_index)
		map->utils.max_index = new_index;
	cpy_tab = (enum e_map **)malloc(sizeof(enum e_map *) * (count_line));
	if (cpy_tab == NULL)
		error(map, ERROR_MALLOC_CPYTAB, NO_VECTOR);
	ft_bzero(cpy_tab, map->utils.count_line);
	i = fill_line(map, cpy_tab);
	if (count_line != map->utils.max_line)
	{
		cpy_tab[i] = (enum e_map *)malloc(sizeof(enum e_map) *
				map->utils.max_index);
		if (cpy_tab[i] == NULL)
			error(map, ERROR_MALLOC_CPYTAB, NO_VECTOR);
		ft_memset(cpy_tab[i], STOP, map->utils.max_index);
	}
	free(map->recup.tab_map);
	map->recup.tab_map = cpy_tab;
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
	cpy_vct = vct_dup(vct);
	clen = vct_clen(cpy_vct, CHAR_WALL);
	if (clen != 0)
		ret = verif_before(cpy_vct, clen);
	vct_del(&cpy_vct);
	return (ret);
}
