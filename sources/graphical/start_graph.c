/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:30 by lfallet           #+#    #+#             */
/*   Updated: 2020/05/14 15:12:57 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_graph(t_map *map)
{
	t_graph	en;

	ft_bzero(&gr, sizeof(gr));
	init_graph(&gr, map);
	init_map(map, &gr);
	start_raycasting(map, &gr);
	process_window(&gr);
}
