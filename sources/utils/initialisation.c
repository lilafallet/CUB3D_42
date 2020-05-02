/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:57:21 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/02 19:00:45 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> /*DEBUG*/

t_state_machine	*get_state_machine(t_state_machine *machine)
{
	static t_state_machine	*gen_state_machine = NULL;

	if (gen_state_machine == NULL)
		gen_state_machine = machine;
	return (gen_state_machine);
}

t_map	*get_map(t_map *map)
{
	static t_map	*gen_map = NULL;

	if (gen_map == NULL)
		gen_map = map;
	return (gen_map);
}

t_graph	*get_graph(t_graph *graph)
{
	static t_graph	*gen_graph = NULL;

	if (gen_graph == NULL)
		gen_graph = graph;
	return (gen_graph);
}

void	ft_free(t_map *map, t_vector *line)
{
	size_t	i;

	ft_printf("TU RENTRES LA QUAND BATARD\n"); //
	i = 0;
	vct_del(&line);
	line = NULL;
	ft_free_tab(NB_TEXTURE, map->recup.str_texture);
	ft_free_tab(BUFFER_SIZE, map->recup.str_map);
	while (i < map->utils.max_line)
		free(map->recup.tab_map[i++]);
	free(map->recup.tab_map);
}
