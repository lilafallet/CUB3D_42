/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:57:21 by lfallet           #+#    #+#             */
/*   Updated: 2020/04/30 22:54:07 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

void	ft_free(t_state_machine *map, t_vector *line)
{
	size_t	i;

	i = 0;
	vct_del(&line);
	line = NULL;
	free(map->str_info_final);
	ft_free_tab(NB_TEXTURE, map->info.str_texture);
	ft_free_tab(BUFFER_SIZE, map->info.str_map);
	while (i < map->info.max_line)
		free(map->info.tab_map[i++]);
	free(map->info.tab_map);
}
