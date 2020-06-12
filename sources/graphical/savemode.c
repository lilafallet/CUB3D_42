/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/12 20:53:35 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	savemode(t_map *map, t_graph *gr)
{
	int	fd;
	int	filesize;
	int	buffer;

	buffer = (PIXOFFSET - (map->recup.resolution[AXE_X] * 3) % PIXOFFSET)
				% PIXOFFSET;
	//pourquoi vaut 0 ?
	//a quoi correspond 3
	printf("buffer = %d\n", buffer); //
	filesize = HEADERSIZE + (3 * (map->recup.resolution[AXE_X] + buffer)
				* map->recup.resolution[AXE_Y]);
	//a quoi correspond 3
	printf("filesize = %d\n", filesize); //
	if ((fd = open("screensh
}
