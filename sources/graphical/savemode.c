/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savemode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallet <lfallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:40:00 by lfallet           #+#    #+#             */
/*   Updated: 2020/06/13 16:55:40 by lfallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static void	int_to_char(unsigned char *src, int n)
{
	src[0] = (unsigned char)(n);
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
	//comprendre cette fonction et sinon essaye de faire comme Fred
}

static void	image_bmp(t_graph *gr, t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	j = 0;
	while (j < map->recup.resolution[AXE_Y])
	{
		i = 0;
		while (i < map->recup.resolution[AXE_X])
		{
			x = i;
			y = map->recup.resolution[AXE_Y] - 1 - j;
			gr->bmp.color = gr->win.data[x + y
								* map->recup.resolution[AXE_X]];
			write(gr->bmp.fd, &gr->bmp.color, 3);
			i++;
		}
		i = 0;
		while (i < (PIXOFFSET - (map->recup.resolution[AXE_X] * 3)
						% PIXOFFSET) % PIXOFFSET)
		{
			write(gr->bmp.fd, &gr->bmp.pad, 1);
			i++;
		}
		j++;
	}
}

void	savemode(t_map *map, t_graph *gr)
{
	int	image_size;

	image_size = 3 * map->recup.resolution[AXE_X] * map->recup.resolution[AXE_Y];
	gr->bmp.size = HEADERSIZE + image_size;
	//A PROTEGER
	gr->bmp.fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	//A PROTEGER
	ft_bzero(gr->bmp.header, HEADERSIZE - INFODATASIZE);
	ft_bzero(gr->bmp.pad, 3);
	gr->bmp.header[TYPEFILE0] = 'B';
	gr->bmp.header[TYPEFILE0 + 1] = 'M';
	gr->bmp.header[PIXOFFSET10] = HEADERSIZE;
	gr->bmp.header[HEADERSIZE14] = INFODATASIZE;
	gr->bmp.header[PLANECOLOR26] = PLANECOLOR;
	gr->bmp.header[BPP28] = BPP;
	int_to_char(&gr->bmp.header[FILESIZE2], gr->bmp.size);
	int_to_char(&gr->bmp.header[IMGWIDTH18], map->recup.resolution[AXE_X]);
	int_to_char(&gr->bmp.header[IMGHEIGHT22], map->recup.resolution[AXE_Y]);
	write(gr->bmp.fd, gr->bmp.header, HEADERSIZE);
	image_bmp(gr, map);
	close(gr->bmp.fd);
	exitred(gr);
}
