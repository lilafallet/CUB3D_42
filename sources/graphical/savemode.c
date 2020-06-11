/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/11 17:53:03 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	savemode(t_map *map, t_graph *gr)
{
	int	fd;

	gr->bmp.width = (size_t)(map->recup.resolution[AXE_X]);	
	gr->bmp.height = (size_t)(map->recup.resolution[AXE_Y]);	
	gr->bmp.totalpix = (unsigned)(gr->bmp.width * gr->bmp.height);
	gr->bmp.totalsize = (unsigned)(gr->bmp.totalpix * PIXOFFSET) + HEADERSIZE;
}
