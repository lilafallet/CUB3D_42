/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:57:21 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/24 14:29:15 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map			*get_map(t_map *map)
{
	static t_map	*gen_map = NULL;

	if (gen_map == NULL)
		gen_map = map;
	return (gen_map);
}

void			ft_free(t_map *map, t_vector *line)
{
	size_t	i;

	i = 0;
	vct_del(&line);
	line = NULL;
	ft_free_tab(NB_TEXTURE, map->recup.str_texture);
	while (i < map->utils.max_line)
		free(map->recup.tab_map[i++]);
	free(map->recup.tab_map);
}
